# binary-diff

## Install

```
$ npm install binary-diff
```

## Usage

```js
const bsdiff = require('binary-diff')

const bufA = Buffer.from('abcd')
const bufB = Buffer.from('abef')

const diffBuffer = bsdiff(bufA, bufB)
```

## Api

```
bsdiff(old: Buffer, new: Buffer) : Buffer
```

## License

MIT © Benoit Lemaire


## Credits

Modification of original implementation from :

- https://github.com/Dezeiraud/bsdiff-nodejs