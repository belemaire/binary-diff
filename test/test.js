const fs = require('fs');
const path = require('path');
const bsdiff = require('../index');
const chai = require('chai');
const chaiFiles = require('chai-files');
chai.use(chaiFiles);
const expect = chai.expect;
const file = chaiFiles.file;

describe('bsdiff', () => {
  describe('#diffBuffer()', () => {
    it('should produce identical output as precomputed patch', () => {
      const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
      const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
     
      const oldBuffer = fs.readFileSync(oldFile); 
      const newBuffer = fs.readFileSync(newFile);
      const patchFile = path.join(__dirname, 'resources/react.patch');
      const patchBufferFile = path.join(__dirname, 'resources/react.test.patch');
      const result = bsdiff.diff(oldBuffer, oldBuffer.length, newBuffer, newBuffer.length);
      fs.writeFileSync(patchBufferFile, result);
      expect(file(patchFile)).to.equal(file(patchBufferFile));
    })
  })
});