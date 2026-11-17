#!/usr/bin/env node
"use strict";

const assert = require("node:assert/strict");
const fs = require("node:fs");
const vm = require("node:vm");

const html = fs.readFileSync("index.html", "utf8");
const start = html.indexOf("function dbfs(");
const end = html.indexOf("function wave(", start);
assert.notEqual(start, -1, "audio metric functions must exist");
assert.notEqual(end, -1, "waveform renderer marker must exist");
const source = html.slice(start, end) + "\nglobalThis.__audioTests={dbfs,showAudioFacts};";
const E = { audioFacts: { textContent: "" } };
const context = { E, Math };
vm.runInNewContext(source, context, { timeout: 2000 });

const api = context.__audioTests;
assert.equal(api.dbfs(0), "-∞");
assert.equal(api.dbfs(1), "0.0 dBFS");
const channels = [
  Float32Array.from([-1, 0, 0.5, 1]),
  Float32Array.from([0, 0.25, -0.25, 0]),
];
const buffer = {
  duration: 2.5,
  sampleRate: 48000,
  numberOfChannels: channels.length,
  length: channels[0].length,
  getChannelData: channel => channels[channel],
};
api.showAudioFacts(buffer);
assert.match(E.audioFacts.textContent, /2\.50 s/);
assert.match(E.audioFacts.textContent, /48\.00 kHz/);
assert.match(E.audioFacts.textContent, /2 canal\/canaux/);
assert.match(E.audioFacts.textContent, /Crête ≈ 0\.0 dBFS/);
assert.match(E.audioFacts.textContent, /RMS ≈ -5\.3 dBFS/);
assert.match(html, /id="waveZoom"/);
assert.match(html, /id="waveOffset"/);
assert.match(html, /id="previewGain"/);
assert.match(html, /gain\.gain\.value=clamp\(\+E\.previewGain\.value\/100/);
assert.match(html, /showAudioFacts\(b\)/);

console.log("PASS: decoded-audio duration/rate/channels/peak/RMS, waveform navigation and monitoring gain invariants.");
