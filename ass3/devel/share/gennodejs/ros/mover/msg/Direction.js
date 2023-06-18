// Auto-generated. Do not edit!

// (in-package mover.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Direction {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.directions = null;
      this.counter = null;
    }
    else {
      if (initObj.hasOwnProperty('directions')) {
        this.directions = initObj.directions
      }
      else {
        this.directions = [];
      }
      if (initObj.hasOwnProperty('counter')) {
        this.counter = initObj.counter
      }
      else {
        this.counter = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Direction
    // Serialize message field [directions]
    bufferOffset = _arraySerializer.string(obj.directions, buffer, bufferOffset, null);
    // Serialize message field [counter]
    bufferOffset = _serializer.int32(obj.counter, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Direction
    let len;
    let data = new Direction(null);
    // Deserialize message field [directions]
    data.directions = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [counter]
    data.counter = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.directions.forEach((val) => {
      length += 4 + _getByteLength(val);
    });
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mover/Direction';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '64e541ae8bb2db4768685ff2c7898ac4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string[] directions
    int32 counter
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Direction(null);
    if (msg.directions !== undefined) {
      resolved.directions = msg.directions;
    }
    else {
      resolved.directions = []
    }

    if (msg.counter !== undefined) {
      resolved.counter = msg.counter;
    }
    else {
      resolved.counter = 0
    }

    return resolved;
    }
};

module.exports = Direction;
