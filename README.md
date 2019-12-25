# bs-jest-fetch-mock [![Travis (.org)](https://img.shields.io/travis/jihchi/bs-jest-fetch-mock)](https://travis-ci.org/jihchi/bs-jest-fetch-mock) [![npm](https://img.shields.io/npm/v/bs-jest-fetch-mock)](https://www.npmjs.com/package/bs-jest-fetch-mock)

> [jest-fetch-mock](https://github.com/jefflau/jest-fetch-mock) bindings for [BuckleScript](https://github.com/bloomberg/bucklescript) in [Reason](https://github.com/facebook/reason)

# Install

```
npm install --save bs-jest-fetch-mock
```

Then add `bs-jest-fetch-mock` as a dependency to `bsconfig.json`:

```diff
  ...
  "bs-dependencies": [
    // add your dependencies here. You'd usually install them normally through `npm install my-dependency`. If my-dependency has a bsconfig.json too, then everything will work seamlessly.
+   "bs-jest-fetch-mock"
  ]
  ...
```

## API

*(TBD)*

# Testing the library

```
npm test
```

this will compile and execute tests with `bs-jest`

# Contributions

Don't hesitate to open a PR with a new binding - while bumping up the amount of covered bindings in the README.
There are tests, use them and write the most simple test you can think of to make sure that the bindings work correctly.
[You can read more about contributing here](CONTRIBUTING.md)
