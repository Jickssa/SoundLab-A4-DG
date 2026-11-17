#!/usr/bin/env node
"use strict";

const assert = require("node:assert/strict");
const fs = require("node:fs");
const vm = require("node:vm");

const html = fs.readFileSync("index.html", "utf8");
const start = html.indexOf("async function getAuditionBuffer(i){");
const end = html.indexOf("async function play(fromSeries=false)", start);
assert.notEqual(start, -1, "A/B audition buffer selector must exist");
assert.notEqual(end, -1, "playback function boundary must exist");

const calls = [];
const native = { id: "patch-1", kind: "native", ref: "audio-1", name: "Patch", key: null };
const audio = { id: "audio-1", kind: "audio", name: "Hardware capture" };
const rawSysex = { id: "syx-1", kind: "syxmsg", ref: "audio-1", name: "Dump message" };
const captureBlob = new Blob(["recorded hardware take"], { type: "audio/webm" });
const S = { auditionMode: "reference", items: [native, audio, rawSysex],
  captures: new Map([["patch-1", { blob: captureBlob }]]) };
const E = {
  synthMode: { value: "auto" },
  previewNote: { value: "48" },
  previewDuration: { value: "2.5" },
  bright: { value: "55" },
  fmAmount: { value: "45" },
  attack: { value: "10" },
  release: { value: "55" },
  width: { value: "65" },
  reverb: { value: "15" },
};
async function decode(item) { calls.push("decode:" + item.id); return "decoded:" + item.id; }
async function ctx() {
  calls.push("ctx");
  return { decodeAudioData: async () => { calls.push("decode-capture:patch-1"); return "decoded:capture:patch-1"; } };
}
function proxy(item) { calls.push("proxy:" + item.id); return "proxy:" + item.id; }

const source = html.slice(start, end) + "\nglobalThis.__abTest={getAuditionBuffer};";
const context = { S, E, decode, ctx, proxy, Error };
vm.runInNewContext(source, context, { timeout: 2000 });
const get = context.__abTest.getAuditionBuffer;

(async () => {
  assert.equal(await get(native), "decoded:capture:patch-1", "A mode should prefer a capture recorded directly on the native item");
  assert.ok(calls.includes("decode-capture:patch-1"));
  S.captures.clear();
  assert.equal(await get(native), "decoded:audio-1", "A mode falls back to the linked audio reference");
  assert.ok(calls.includes("decode:audio-1"));

  S.auditionMode = "proxy";
  assert.equal(await get(native), "proxy:patch-1", "B mode must use the native sound proxy");
  assert.ok(calls.includes("proxy:patch-1"));

  S.auditionMode = "reference";
  assert.equal(await get(audio), "decoded:audio-1", "audio files always play as original audio");

  assert.equal(await get(rawSysex), "decoded:audio-1", "raw SysEx can only be auditioned via a linked real recording");
  S.auditionMode = "proxy";
  await assert.rejects(get(rawSysex), /no native proxy/i);

  const unlinked = { id: "patch-2", kind: "native", name: "No reference" };
  assert.equal(await get(unlinked), "proxy:patch-2", "unlinked native sounds remain proxy-auditionable");

  console.log("PASS: A/B selects direct capture or linked reference vs native proxy; raw SysEx never becomes synthetic audio.");
})().catch(error => {
  console.error(error);
  process.exitCode = 1;
});
