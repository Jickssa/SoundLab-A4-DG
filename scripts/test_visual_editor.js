#!/usr/bin/env node
"use strict";

const assert = require("node:assert/strict");
const fs = require("node:fs");
const vm = require("node:vm");

const html = fs.readFileSync("index.html", "utf8");
const start = html.indexOf("const MAX_EDITOR_BUFFER_BYTES=");
const end = html.indexOf("function wave(b){", start);
assert.notEqual(start, -1, "visual editor engine must exist");
assert.notEqual(end, -1, "visual editor engine boundary must exist");

class FakeAudioBuffer {
  constructor(channels, sampleRate) {
    this.numberOfChannels = channels.length;
    this.length = channels[0]?.length ?? 0;
    this.sampleRate = sampleRate;
    this.channels = channels.map(channel => Float32Array.from(channel));
  }
  getChannelData(channel) { return this.channels[channel]; }
  copyToChannel(source, channel) { this.channels[channel].set(source); }
}

const sourceBuffer = new FakeAudioBuffer([
  Float32Array.from([0.2, 0.4, 0.6, 0.8]),
  Float32Array.from([-0.2, -0.4, -0.6, -0.8])
], 48000);
const item = { id: "audio-1", kind: "audio", name: "original.wav", ref: null };
const S = {
  ctx: { createBuffer: (channels, length, rate) =>
    new FakeAudioBuffer(Array.from({ length: channels }, () => new Float32Array(length)), rate) },
  items: [item], selected: item.id, auditionMode: "proxy",
  edits: new Map(), captures: new Map(), editorState: null, editorOpen: true,
  editorMode: "select", envelopePreview: [], editorPointer: null
};
const E = {
  edStatus: { textContent: "", className: "" },
  edGain: { value: "50" },
  edUndo: { disabled: false }, edRedo: { disabled: false },
  edDiscard: { disabled: false },
  editDirty: { textContent: "", className: "" },
  edSelection: { textContent: "" },
  edSelect: { classList: { toggle() {} } },
  edEnvelope: { classList: { toggle() {} } },
  wave: { parentElement: { classList: { toggle() {} } } },
  visualEditor: { classList: { add() {}, remove() {} } },
  editOpen: { textContent: "" }
};
let visualRedraws = 0;
function current() { return item; }
function editorKey(i) { return i.id + "|audio"; }
function editorSourceToken(i) { return "audio:" + i.id; }
async function getBaseAuditionBuffer() { return sourceBuffer; }
async function ctx() { return S.ctx; }
function wave() { visualRedraws++; }
function updateEditorUI() {}
function redrawEditor() { visualRedraws++; }
function render() {}
function renderDetail() {}
function dl() {}
function wav() {}
function itemFactory() { return {}; }
function canOpenVisualEditor() { return true; }
function log() {}
function clamp(value, min, max) { return Math.max(min, Math.min(max, value)); }

const source = html.slice(start, end) +
  "\nglobalThis.__visualEditorTest = { ensureVisualEditor, applyEditorGain, applyEditorFade, applyEditorNormalize, applyEditorReverse, applyEditorSilence, applyEditorTrim, applyEditorEnvelope, undoEditor, redoEditor, resetEditor, audioBufferBytes, MAX_EDITOR_BUFFER_BYTES, MAX_EDITOR_HISTORY_BYTES, MAX_EDITOR_SESSION_BYTES, sessionEditorBytes };";
const context = {
  S, E, current, editorKey, editorSourceToken, getBaseAuditionBuffer, ctx,
  wave, updateEditorUI, redrawEditor, render, renderDetail, dl, wav,
  item: itemFactory, canOpenVisualEditor, log, clamp,
  Math, Float32Array, Uint8Array, ArrayBuffer, Error, Date,
  crypto: { randomUUID: () => "copy-id" }
};
vm.runInNewContext(source, context, { timeout: 3000 });
const api = context.__visualEditorTest;

function makeState(channels, selection = null, sampleRate = 4) {
  const buffer = new FakeAudioBuffer(channels, sampleRate);
  return { key: "test|audio", token: "test-token", buffer, selection,
    undo: [], redo: [], historyBytes: 0, dirty: false };
}
function values(state, channel = 0) { return Array.from(state.buffer.getChannelData(channel)); }
function near(actual, expected, epsilon = 1e-6) { return actual.length === expected.length && actual.every((value, index) => Math.abs(value - expected[index]) <= epsilon); }
function setState(state) { S.editorState = state; S.edits.set(state.key, state); }

(async () => {
  const editor = await api.ensureVisualEditor();
  assert.notEqual(editor.buffer, sourceBuffer, "editing must use a private working buffer");
  assert.ok(near(values(editor), [0.2, 0.4, 0.6, 0.8]));
  editor.selection = { start: 1, end: 3 };
  setState(editor);
  api.applyEditorGain();
  assert.ok(near(values(editor), [0.2, 0.2, 0.3, 0.8]), "gain must stay inside the selected range");
  assert.ok(near(values(editor, 1), [-0.2, -0.2, -0.3, -0.8]), "gain must process every channel");
  assert.ok(near(values({buffer: sourceBuffer}), [0.2, 0.4, 0.6, 0.8]), "source samples must remain untouched");
  api.undoEditor();
  assert.ok(near(values(editor), [0.2, 0.4, 0.6, 0.8]));
  api.redoEditor();
  assert.ok(near(values(editor), [0.2, 0.2, 0.3, 0.8]));

  let state = makeState([[1, 1, 1, 1]], { start: 0, end: 4 });
  setState(state);
  api.applyEditorFade("in");
  assert.ok(Math.abs(values(state)[0] - 0) < 1e-7);
  assert.ok(Math.abs(values(state)[1] - 1 / 3) < 1e-6);
  assert.ok(Math.abs(values(state)[2] - 2 / 3) < 1e-6);
  assert.equal(values(state)[3], 1);

  state = makeState([[1, 1, 1, 1]], { start: 0, end: 4 });
  setState(state);
  api.applyEditorFade("out");
  assert.ok(near(values(state), [1, 2 / 3, 1 / 3, 0]));

  state = makeState([[0, 1, 2, 3, 4]], { start: 1, end: 4 });
  setState(state);
  api.applyEditorReverse();
  assert.deepEqual(values(state), [0, 3, 2, 1, 4]);

  state = makeState([[1, 0.5, -0.5, 1]], { start: 1, end: 3 });
  setState(state);
  api.applyEditorSilence();
  assert.deepEqual(values(state), [1, 0, 0, 1]);
  api.undoEditor();
  assert.ok(near(values(state), [1, 0.5, -0.5, 1]));

  state = makeState([[0.2, -0.5, 0.1, 0.25]], { start: 0, end: 4 });
  setState(state);
  api.applyEditorNormalize();
  const peak = Math.max(...values(state).map(Math.abs));
  assert.ok(Math.abs(peak - Math.pow(10, -1 / 20)) < 1e-6, "normalization target must be -1 dBFS");

  state = makeState([[0, 1, 2, 3, 4, 5]], { start: 1, end: 4 });
  setState(state);
  api.applyEditorTrim();
  assert.deepEqual(values(state), [1, 2, 3], "trim must retain selected samples only");
  assert.equal(state.buffer.length, 3);
  api.undoEditor();
  assert.deepEqual(values(state), [0, 1, 2, 3, 4, 5], "undo trim must restore the complete clip");
  assert.equal(state.selection?.start, 1, "undo trim must restore selection start");
  assert.equal(state.selection?.end, 4, "undo trim must restore selection end");
  api.redoEditor();
  assert.deepEqual(values(state), [1, 2, 3], "redo trim must crop again");

  state = makeState([[1, 1, 1, 1, 1]], null);
  setState(state);
  api.applyEditorEnvelope(1, 4, [{ frame: 1, gain: 0 }, { frame: 4, gain: 2 }]);
  assert.ok(near(values(state), [1, 0, 2 / 3, 4 / 3, 1]), "envelope must affect only its explicit visible range");
  api.undoEditor();
  assert.deepEqual(values(state), [1, 1, 1, 1, 1], "envelope must be undoable");

  await api.resetEditor();
  assert.ok(near(values(S.editorState), [0.2, 0.4, 0.6, 0.8]), "reset must reload the original decoded buffer");
  assert.ok(near(values({buffer: sourceBuffer}), [0.2, 0.4, 0.6, 0.8]), "reset must never mutate imported source samples");
  assert.equal(S.editorState.undo.length, 0);
  assert.ok(visualRedraws > 0);

  assert.equal(api.audioBufferBytes(sourceBuffer), 4 * 2 * 4);
  assert.ok(api.MAX_EDITOR_HISTORY_BYTES <= 128 * 1024 * 1024);
  assert.ok(api.MAX_EDITOR_BUFFER_BYTES <= 128 * 1024 * 1024);
  assert.match(html, /id="edDiscard"/);
  assert.match(html, /function discardVisualEdit\(\)/);
  assert.equal(api.MAX_EDITOR_SESSION_BYTES, 256 * 1024 * 1024);
  S.edits.clear();
  S.edits.set("memory-fixture", {
    buffer: { length: api.MAX_EDITOR_SESSION_BYTES / 4, numberOfChannels: 1 },
    historyBytes: 0
  });
  assert.equal(api.sessionEditorBytes(), api.MAX_EDITOR_SESSION_BYTES);
  S.editorState = null;
  await assert.rejects(api.ensureVisualEditor(), /Budget mémoire de session atteint/);
  S.edits.clear();

  console.log("PASS: isolated source buffer, multichannel range gain, undo/redo, fades, normalize, reverse, silence, trim, envelope scope and reset.");
})().catch(error => {
  console.error(error);
  process.exitCode = 1;
});
