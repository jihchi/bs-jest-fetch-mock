# bs-jest-fetch-mock [![Travis (.org)](https://img.shields.io/travis/jihchi/bs-jest-fetch-mock)](https://travis-ci.org/jihchi/bs-jest-fetch-mock) [![npm](https://img.shields.io/npm/v/bs-jest-fetch-mock)](https://www.npmjs.com/package/bs-jest-fetch-mock) [![Coveralls github](https://img.shields.io/coveralls/github/jihchi/bs-jest-fetch-mock)](https://coveralls.io/github/jihchi/bs-jest-fetch-mock) ![npm](https://img.shields.io/npm/dm/bs-jest-fetch-mock) ![NPM](https://img.shields.io/npm/l/bs-jest-fetch-mock)

> [jest-fetch-mock](https://github.com/jefflau/jest-fetch-mock) bindings for [BuckleScript](https://github.com/bloomberg/bucklescript) in [Reason](https://github.com/facebook/reason)

# Installation

**Prerequisite**: you have installed [jest-fetch-mock](https://github.com/jefflau/jest-fetch-mock#installation-and-setup).

```sh
npm install --save-dev bs-jest-fetch-mock

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

`BsJestFetchMock` is the root namespace module.

## `JestFetchMock.mockResponse`

**string**

```reason
JestFetchMock.mockResponse(`Str({|{ "body": "ok" }|}), Js.Undefined.empty);
```

**string with init**

```reason
JestFetchMock.mockResponse(
  `Str({|{ "body": "ok" }|}),
  Js.Undefined.return(
    init(
      ~status=204,
      ~statusText="nothing for you",
      ~headers=Js.Dict.fromList([("Authorization", "Bearer <token>")]),
      (),
    ),
  ),
);
```

**function (with string)**

```reason
JestFetchMock.mockResponse(
  `FnStr(
    req =>
      if (Fetch.Request.url(req) == "http://parsed_url/") {
        resolve({|{ "body": "ok" }|});
      } else {
        resolve("");
      },
  ),
  Js.Undefined.empty,
);
```

**function (with response)**

```reason
JestFetchMock.mockResponse(
  `FnResp(
    req =>
      if (Fetch.Request.url(req) == "http://parsed_url/") {
        response(
          ~body={|{ "body": "ok" }|},
          ~status=200,
          ~statusText="OK",
          ~headers=
            Js.Dict.fromList([("Authorization", "Bearer <token>")]),
          (),
        )
        |> resolve,
      } else {
        response(
          ~body="",
          ~status=418,
          ~statusText="I'm a teapot",
          ~headers=
            Js.Dict.fromList([("Authorization", "Bearer <token>")]),
          (),
        )
        |> resolve,
      },
  ),
  Js.Undefined.empty,
);
```

## `JestFetchMock.mockResponseOnce`

Same function signature as `mockResponse`.

## `JestFetchMock.mockResponsesStr`

```reason
JestFetchMock.mockResponsesStr([|
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

## `JestFetchMock.mockResponsesFn`

```reason
JestFetchMock.mockResponsesFn([|
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

## `JestFetchMock.mockResponsesFnResp`

```reason
JestFetchMock.mockResponsesFnResp([|
  (
	  _req =>
      response(
        ~body={|"first body"|},
        ~status=418,
        ~statusText="I'm a teapot",
        (),
      )
      |> resolve,
	  Js.Undefined.empty
	),
  (
    _req =>
      response(
        ~body={|"second body"|},
        (),
      )
      |> resolve,
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

## `JestFetchMock.mockReject`

**string**

```reason
JestFetchMock.mockReject(`Str({|{ "body": "ok" }|}));
```

**function**

```reason
JestFetchMock.mockReject(`FnStr(_req => Js.Promise.resolve({|{ "body": "ok" }|})));
```

## `JestFetchMock.mockRejectOnce`

Same function signature as `mockReject`.

## `JestFetchMock.mockAbort`

```reason
JestFetchMock.mockReject();
```

## `JestFetchMock.mockAbortOnce`

Same function signature as `mockAbort`.

## `JestFetchMock.resetMocks`

```reason
JestFetchMock.resetMocks();
```

# Testing the library

```
npm test
```

this will compile and execute tests with `bs-jest`

# Contributions

Don't hesitate to open a PR with a new binding - while bumping up the amount of covered bindings in the README.
There are tests, use them and write the most simple test you can think of to make sure that the bindings work correctly.
