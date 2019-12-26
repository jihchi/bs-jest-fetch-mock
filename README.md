# bs-jest-fetch-mock [![Travis (.org)](https://img.shields.io/travis/jihchi/bs-jest-fetch-mock)](https://travis-ci.org/jihchi/bs-jest-fetch-mock) [![npm](https://img.shields.io/npm/v/bs-jest-fetch-mock)](https://www.npmjs.com/package/bs-jest-fetch-mock) [![Coveralls github](https://img.shields.io/coveralls/github/jihchi/bs-jest-fetch-mock)](https://coveralls.io/github/jihchi/bs-jest-fetch-mock)

> [jest-fetch-mock](https://github.com/jefflau/jest-fetch-mock) bindings for [BuckleScript](https://github.com/bloomberg/bucklescript) in [Reason](https://github.com/facebook/reason)

# Installation

```sh
npm install --save bs-jest-fetch-mock

# or ...

yarn add -D bs-jest-fetch-mock
```

# Usage

Add to `bsconfig.json`

```diff
  ...
  "bs-dependencies": [
+   "bs-jest-fetch-mock"
  ]
  ...
```

## API

For more example, please refer to [`JestFetchMock_test.re`](/__tests__/JestFetchMock_test.re)

## `BsJestFetchMock.mockResponse`

**string**

```reason
BsJestFetchMock.mockResponse(~response=Str({|{ "body": "ok" }|}), ());
```

**function**

```reason
BsJestFetchMock.mockResponse(
  ~response=
    Fn(
      req =>
        Fetch.Request.url(req) == "http://parsed_url/" ?
          Js.Promise.resolve({|{ "body": "ok" }|}) : Js.Promise.resolve(""),
    ),
  (),
);
```

**with init**

```reason
BsJestFetchMock.mockResponse(
  ~response=Str({|{ "body": "ok" }|}),
  ~init=
    init(
      ~status=200,
      ~statusText="ok",
      ~headers=Js.Dict.fromList([("Authorization", "Bearer <token>")]),
    ),
  (),
);
```

## `BsJestFetchMock.mockResponseOnce`

Same function signature as `mockResponse`.

## `BsJestFetchMock.mockResponsesStr`

```reason
BsJestFetchMock.mockResponsesStr([|
  ({|"first body"|}, Js.Undefined.empty),
  (
    {|"second body"|},
    Js.Undefined.return(
      init(
        ~status=200,
        ~statusText="ok",
        ~headers=Js.Dict.fromList([("Authorization", "Bearer <token>")]),
        (),
      ),
    ),
  ),
|]);
```

## `BsJestFetchMock.mockResponsesFn`

```reason
BsJestFetchMock.mockResponsesFn([|
  (_req => Js.Promise.resolve({|"first body"|}), Js.Undefined.empty),
  (
    _req => Js.Promise.resolve({|"second body"|}),
    Js.Undefined.return(
      init(
        ~status=200,
        ~statusText="ok",
        ~headers=Js.Dict.fromList([("Authorization", "Bearer <token>")]),
        (),
      ),
    ),
  ),
|]);
```

## `BsJestFetchMock.mockReject`

**string**
```reason
BsJestFetchMock.mockReject(Str({|{ "body": "ok" }|}));
```

**function**
```reason
BsJestFetchMock.mockReject(Fn(_req => Js.Promise.resolve({|{ "body": "ok" }|})));
```

## `BsJestFetchMock.mockRejectOnce`

Same function signature as `mockReject`.

## `BsJestFetchMock.mockAbort`

```reason
BsJestFetchMock.mockReject();
```

## `BsJestFetchMock.mockAbortOnce`

Same function signature as `mockAbort`.

## `BsJestFetchMock.resetMocks`

```reason
BsJestFetchMock.resetMocks();
```

# Testing the library

```
npm test
```

this will compile and execute tests with `bs-jest`

# Contributions

Don't hesitate to open a PR with a new binding - while bumping up the amount of covered bindings in the README.
There are tests, use them and write the most simple test you can think of to make sure that the bindings work correctly.
