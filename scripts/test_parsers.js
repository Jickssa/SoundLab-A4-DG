#!/usr/bin/env node
"use strict";

const assert = require("node:assert/strict");
const fs = require("node:fs");
const vm = require("node:vm");

const html = fs.readFileSync("index.html", "utf8");
function extract(start, end) {
  const a = html.indexOf(start);
  const b = html.indexOf(end, a + start.length);
  assert.notEqual(a, -1, "missing source marker: " + start);
  assert.notEqual(b, -1, "missing source end marker: " + end);
  return html.slice(a, b);
}

const limits = {
  maxZipBytes: 128 * 1024 * 1024,
  maxEntryBytes: 64 * 1024 * 1024,
  maxExpandedBytes: 256 * 1024 * 1024,
  maxEntries: 2048,
};
const state = { expandedBytes: 0 };
const context = {
  LIMITS: limits,
  S: state,
  TextDecoder,
  Uint8Array,
  DataView,
  ArrayBuffer,
  Blob,
  Response,
  DecompressionStream,
};
const source = [
  extract("function crc32(a){", "function ascii("),
  extract("function readZip(buf){", "async function unzip("),
  extract("async function unzip(z,e){", "async function importFiles("),
  extract("function split(a){", "async function syx("),
  "globalThis.__soundlabTests = { readZip, unzip, split, crc32 };",
].join("\n");
vm.runInNewContext(source, context, { timeout: 2000 });
const api = context.__soundlabTests;

function makeStoredZip(filename, payload) {
  const name = Buffer.from(filename, "utf8");
  const data = Buffer.from(payload, "utf8");
  const crc = api.crc32(new Uint8Array(data));
  const localLength = 30 + name.length + data.length;
  const centralLength = 46 + name.length;
  const buffer = new ArrayBuffer(localLength + centralLength + 22);
  const view = new DataView(buffer);
  const bytes = new Uint8Array(buffer);

  view.setUint32(0, 0x04034b50, true);
  view.setUint16(4, 20, true);
  view.setUint32(14, crc, true);
  view.setUint32(18, data.length, true);
  view.setUint32(22, data.length, true);
  view.setUint16(26, name.length, true);
  bytes.set(name, 30);
  bytes.set(data, 30 + name.length);

  let p = localLength;
  view.setUint32(p, 0x02014b50, true);
  view.setUint16(p + 4, 20, true);
  view.setUint16(p + 6, 20, true);
  view.setUint32(p + 16, crc, true);
  view.setUint32(p + 20, data.length, true);
  view.setUint32(p + 24, data.length, true);
  view.setUint16(p + 28, name.length, true);
  bytes.set(name, p + 46);

  p += centralLength;
  view.setUint32(p, 0x06054b50, true);
  view.setUint16(p + 8, 1, true);
  view.setUint16(p + 10, 1, true);
  view.setUint32(p + 12, centralLength, true);
  view.setUint32(p + 16, localLength, true);
  return buffer;
}

(async () => {
  const zipBytes = makeStoredZip("fixture.txt", "SoundLab regression fixture");
  const archive = api.readZip(zipBytes);
  assert.equal(archive.entries.length, 1);
  assert.equal(archive.entries[0].name, "fixture.txt");
  const payload = await api.unzip(archive, archive.entries[0]);
  assert.equal(Buffer.from(payload).toString("utf8"), "SoundLab regression fixture");
  assert.equal(state.expandedBytes, payload.length);

  state.expandedBytes = 0;
  const corrupt = makeStoredZip("corrupt.txt", "payload");
  new Uint8Array(corrupt)[30 + Buffer.byteLength("corrupt.txt")] ^= 0x01;
  const corruptArchive = api.readZip(corrupt);
  await assert.rejects(api.unzip(corruptArchive, corruptArchive.entries[0]), /CRC mismatch/);

  state.expandedBytes = 0;
  const limited = api.readZip(makeStoredZip("large.txt", "0123456789"));
  limits.maxExpandedBytes = 4;
  await assert.rejects(api.unzip(limited, limited.entries[0]), /cumulative expanded-size limit/);
  limits.maxExpandedBytes = 256 * 1024 * 1024;

  const parsed = api.split([0x00, 0xf0, 0x00, 0x20, 0x3c, 0x01, 0xf7, 0xf0, 0x01]);
  assert.equal(parsed.msg.length, 1);
  assert.equal(parsed.warn.length, 1);
  assert.match(parsed.warn[0], /Unterminated/);

  const syxStart = html.indexOf("async function syx(");
  const syxEnd = html.indexOf("function current()", syxStart);
  const syxSource = html.slice(syxStart, syxEnd);
  assert.match(syxSource, /previewable:false/);
  assert.match(html, /if\(!\['a4','dn'\]\.includes\(E\.target\.value\)\)/);
  assert.match(html, /E\.sysexAck\.checked/);
  assert.match(html, /attack=\+E\.attack\.value/);
  assert.match(html, /wet=\+E\.reverb\.value/);
  assert.match(html, /play\(true\)/);
  assert.match(html, /indexedDB\.open\('ElektronSoundLabLibrary',1\)/);
  assert.match(html, /async function saveLocalLibrary\(\)/);
  assert.match(html, /async function restoreLocalLibrary\(\)/);
  assert.match(html, /async function deleteLocalLibrary\(\)/);
  assert.match(html, /recordType:'capture'/);
  assert.match(html, /localStatus/);
  assert.match(html, /function showAudioFacts\(b\)/);
  assert.match(html, /function dbfs\(value\)/);
  assert.match(html, /src\.connect\(gain\);gain\.connect\(ac\.destination\)/);
  assert.match(html, /E\.waveZoom\.oninput/);
  assert.match(html, /E\.waveOffset\.oninput/);
  assert.match(html, /indexedDB\.open\('ElektronSoundLabLibrary',1\)/);
  assert.match(html, /async function saveLocalLibrary\(\)/);
  assert.match(html, /async function restoreLocalLibrary\(\)/);
  assert.match(html, /async function deleteLocalLibrary\(\)/);
  assert.match(html, /recordType:'capture'/);
  assert.match(html, /localStatus/);

  console.log("PASS: ZIP round-trip, CRC rejection, expansion cap, SysEx framing and v3.2 safety/audition invariants.");
})().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
