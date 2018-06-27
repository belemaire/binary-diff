const fs = require('fs');
const path = require('path');
const bsdiff = require('../index');
const chai = require('chai');
const chaiFiles = require('chai-files');
chai.use(chaiFiles);
const expect = chai.expect;
const file = chaiFiles.file;

describe('bsdiff', () => {
  describe('#diff() + #patch()', () => {
    it('should generate an file identical to original file after appling a patch to an old file', () => {
      const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
      const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
      const patchFile = path.join(__dirname, 'resources/react.patch');
      const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

      bsdiff.diff(oldFile, newFile, patchFile);
      bsdiff.patch(oldFile, generatedFile, patchFile);
    });
  });

  describe('#diffBuffer()', () => {
    it('should produce identical output as diff', () => {
      const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
      const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
      const patchFile = path.join(__dirname, 'resources/react.patch');
      bsdiff.diff(oldFile, newFile, patchFile);

      const oldBuffer = fs.readFileSync(oldFile); 
      const newBuffer = fs.readFileSync(newFile);
      const patchBufferFile = path.join(__dirname, 'resources/react.buffer.patch');
      bsdiff.diffBuffer(oldBuffer, oldBuffer.length, newBuffer, newBuffer.length, patchBufferFile);

      expect(file(patchFile)).to.equal(file(patchBufferFile));
    })
  })
});