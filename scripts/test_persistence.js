#!/usr/bin/env node
"use strict";

const assert = require("node:assert/strict");
const fs = require("node:fs");
const vm = require("node:vm");

const html = fs.readFileSync("index.html", "utf8");
const start = html.indexOf("function openLibraryDB(){");
const end = html.indexOf("function inventory(){", start);
assert.notEqual(start, -1, "IndexedDB persistence functions must exist");
assert.notEqual(end, -1, "IndexedDB persistence section must end");
const source = html.slice(start, end) +
  "\nglobalThis.__persistenceTests={openLibraryDB,saveLocalLibrary,restoreLocalLibrary,deleteLocalLibrary,inspectLocalLibrary};";

class FakeStore {
  constructor(db, tx) { this.db = db; this.tx = tx; }
  clear() { this.tx.schedule(() => this.db.records.clear()); return {}; }
  put(record) {
    this.tx.schedule(() => this.db.records.set(record.id, structuredClone(record)));
    return {};
  }
  count() {
    const req = {};
    this.tx.schedule(() => { req.result = this.db.records.size; req.onsuccess?.(); });
    return req;
  }
  getAll() {
    const req = {};
    this.tx.schedule(() => { req.result = [...this.db.records.values()].map(record => structuredClone(record)); req.onsuccess?.(); });
    return req;
  }
}
class FakeTransaction {
  constructor(db) {
    this.db = db; this.pending = 0; this.finished = false; this.initialising = true;
    queueMicrotask(() => { this.initialising = false; this.finishIfReady(); });
  }
  objectStore(name) {
    assert.equal(name, "entries");
    return new FakeStore(this.db, this);
  }
  schedule(fn) {
    this.pending++;
    queueMicrotask(() => {
      try { fn(); }
      catch (error) { this.error = error; this.onerror?.(); }
      finally { this.pending--; this.finishIfReady(); }
    });
  }
  finishIfReady() {
    if (this.initialising || this.pending || this.finished) return;
    this.finished = true;
    queueMicrotask(() => this.error ? this.onabort?.() : this.oncomplete?.());
  }
}
class FakeDatabase {
  constructor() {
    this.records = new Map();
    this.hasEntries = false;
    this.objectStoreNames = { contains: name => name === "entries" && this.hasEntries };
  }
  createObjectStore(name) {
    assert.equal(name, "entries");
    this.hasEntries = true;
    return new FakeStore(this, new FakeTransaction(this));
  }
  transaction(name, mode) {
    assert.equal(name, "entries");
    assert.ok(mode === "readonly" || mode === "readwrite");
    return new FakeTransaction(this);
  }
  close() {}
}
const fakeDatabase = new FakeDatabase();
const fakeIndexedDB = {
  open(name, version) {
    assert.equal(name, "ElektronSoundLabLibrary");
    assert.equal(version, 1);
    const req = {};
    queueMicrotask(() => {
      req.result = fakeDatabase;
      req.onupgradeneeded?.();
      req.onsuccess?.();
    });
    return req;
  },
};
const S = {
  items: [
    { id: "patch-1", name: "Native patch", path: "Native.afsnd", ext: "afsnd",
      kind: "native", size: 12, blob: new Blob(["source"]), payload: new Uint8Array([1, 2, 3]),
      tags: ["bass"], device: "a4", status: "proxy", previewable: true, transferable: false,
      warning: [], category: "bass", favorite: true, ref: "audio-1" },
    { id: "audio-1", name: "Reference.wav", path: "Reference.wav", ext: "wav",
      kind: "audio", size: 8, blob: new Blob(["audio"]), device: "audio", previewable: true,
      transferable: false, warning: [], category: "keys", favorite: false },
  ],
  captures: new Map([["patch-1", { blob: new Blob(["capture"], { type: "audio/webm" }), url: "blob:old" }]),
  dbPromise: null, selected: "patch-1", series: { ids: [], index: 0, active: false },
};
const classList = { add() {}, remove() {} };
const E = {
  localStatus: { textContent: "" },
  noItem: { classList },
  inspector: { classList },
};
const logs = [];
const context = {
  window: { indexedDB: fakeIndexedDB },
  indexedDB: fakeIndexedDB,
  S, E,
  Blob, Map, Promise, Error, URL, structuredClone,
  console,
  confirm: () => true,
  log: (...args) => logs.push(args),
  item: value => ({ id: "generated", selected: false, favorite: false, tags: [], warning: [], ...value }),
  stop: () => {},
  render: () => {},
  current: () => S.items.find(x => x.id === S.selected) || null,
  renderDetail: () => {},
  fmt: n => String(n),
};
vm.runInNewContext(source, context, { timeout: 2000 });
const api = context.__persistenceTests;

(async () => {
  await api.saveLocalLibrary();
  assert.equal(fakeDatabase.records.size, 3, "two source files plus one recorded capture should be saved");
  assert.match(E.localStatus.textContent, /2 fichier\(s\), 1 capture\(s\)/);

  S.items = [];
  S.captures.clear();
  S.selected = null;
  await api.restoreLocalLibrary();
  assert.equal(S.items.length, 2);
  assert.equal(S.items.find(x => x.id === "patch-1").favorite, true);
  assert.equal(S.items.find(x => x.id === "patch-1").ref, "audio-1");
  assert.deepEqual(Array.from(S.items.find(x => x.id === "patch-1").payload), [1, 2, 3]);
  assert.equal(S.captures.size, 1);
  assert.equal(S.captures.get("patch-1").blob.type, "audio/webm");
  assert.equal(S.selected, "patch-1");

  await api.deleteLocalLibrary();
  assert.equal(fakeDatabase.records.size, 0, "persistent store should be emptied");
  assert.equal(S.items.length, 2, "deleting the backup must not clear the active session");
  assert.match(E.localStatus.textContent, /Sauvegarde locale effacée/);

  console.log("PASS: IndexedDB save, restore, favourite/ref metadata, binary payload, captured audio and persistent deletion.");
})().catch(error => {
  console.error(error);
  process.exitCode = 1;
});
