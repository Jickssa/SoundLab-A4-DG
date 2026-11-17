#!/usr/bin/env node
"use strict";

const assert = require("node:assert/strict");
const fs = require("node:fs");
const vm = require("node:vm");

const html = fs.readFileSync("index.html", "utf8");
const start = html.indexOf("const ELEKTRON_SOUND_TAGS={");
const end = html.indexOf("async function syx(", start);
assert.notEqual(start, -1, "missing Elektron Sound SysEx parser");
assert.notEqual(end, -1, "missing end of Elektron Sound SysEx parser");
const source = html.slice(start, end) +
  "\nglobalThis.__soundParser = { ELEKTRON_SOUND_TAGS, decodeElektronSoundPayload, inspectElektronSoundMessage };";
const context = { Uint8Array };
vm.runInNewContext(source, context, { timeout: 2000 });
const parser = context.__soundParser;

function encode7Bit(raw) {
  const encoded = [];
  for (let offset = 0; offset < raw.length; offset += 7) {
    const group = raw.slice(offset, offset + 7);
    let msb = 0;
    for (let i = 0; i < group.length; i++) {
      msb |= ((group[i] >> 7) & 1) << (6 - i);
    }
    encoded.push(msb, ...Array.from(group, value => value & 0x7f));
  }
  return encoded;
}

function encode14(value) {
  return [(value >> 7) & 0x7f, value & 0x7f];
}

function makeSound({ modelId, slot = 7, name = "TEST SOUND", tags = [] }) {
  const raw = new Uint8Array(96);
  const nameBytes = Array.from(name, char => char.charCodeAt(0) & 0xff).slice(0, 15);
  raw.set(nameBytes, 12);
  raw[12 + nameBytes.length] = 0;
  for (const tag of tags) {
    assert.ok(Number.isInteger(tag) && tag >= 0 && tag < 32);
    raw[11 - Math.floor(tag / 8)] |= 1 << (tag % 8);
  }

  const encoded = encode7Bit(raw);
  const checksum = encode14(encoded.reduce((sum, byte) => sum + byte, 0) & 0x3fff);
  const length = encode14(encoded.length + 5);
  return Uint8Array.from([
    0xf0, 0x00, 0x20, 0x3c, modelId,
    0x00, 0x53, 0x01, 0x01, slot,
    ...encoded, ...checksum, ...length, 0xf7
  ]);
}

function inspect(bytes) {
  return parser.inspectElektronSoundMessage(bytes);
}

const dn = inspect(makeSound({ modelId: 0x0d, name: "FM BELL", tags: [0, 11, 31] }));
assert.equal(dn.ok, true);
assert.equal(dn.model, "dn");
assert.equal(dn.modelId, 0x0d);
assert.equal(dn.modelLabel, "Digitone MK1");
assert.equal(dn.slot, 7);
assert.equal(dn.name, "FM BELL");
assert.deepEqual(Array.from(dn.tags), ["KICK", "LEAD", "FAV"]);
assert.equal(dn.checksumValid, true);
assert.equal(dn.lengthValid, true);

const a4 = inspect(makeSound({ modelId: 0x06, slot: 2, name: "ANALOG BASS", tags: [0, 25, 31] }));
assert.equal(a4.ok, true);
assert.equal(a4.model, "a4");
assert.equal(a4.modelLabel, "Analog Four / Analog Keys");
assert.equal(a4.slot, 2);
assert.deepEqual(Array.from(a4.tags), ["BASS", "ACID", "FAVOURITE"]);

const badChecksum = makeSound({ modelId: 0x0d });
badChecksum[badChecksum.length - 5] ^= 1;
assert.equal(inspect(badChecksum).ok, false);
assert.match(inspect(badChecksum).reason, /checksum/i);

const badLength = makeSound({ modelId: 0x0d });
badLength[badLength.length - 3] ^= 1;
assert.equal(inspect(badLength).ok, false);
assert.match(inspect(badLength).reason, /length/i);

const badPrefix = makeSound({ modelId: 0x0d });
badPrefix[6] = 0x52;
assert.equal(inspect(badPrefix).ok, false);
assert.match(inspect(badPrefix).reason, /prefix/i);

const unsupportedModel = makeSound({ modelId: 0x07 });
assert.equal(inspect(unsupportedModel).ok, false);
assert.match(inspect(unsupportedModel).reason, /Model ID/i);

const bad7Bit = makeSound({ modelId: 0x0d });
bad7Bit[10] = 0x80;
assert.equal(inspect(bad7Bit).ok, false);
assert.match(inspect(bad7Bit).reason, /7-bit/i);

assert.throws(() => parser.decodeElektronSoundPayload(Uint8Array.from([0x00])), /8-in-7/i);
assert.equal(inspect(Uint8Array.from([0xf0, 0x01, 0xf7])).ok, false);

console.log("PASS: Analog Four and Digitone Sound SysEx framing, checksum, length, model ID, 7-bit payload, name and tags.");
