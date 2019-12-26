type response =
  | Str(string)
  | Fn(unit => Js.Promise.t(string));

[@bs.deriving abstract]
type init = {
  [@bs.optional]
  status: int,
  [@bs.optional]
  statusText: string,
  [@bs.optional]
  headers: Js.Dict.t(string),
};

let responseToParameter = response =>
  switch (response) {
  | Str(str) => `Str(str)
  | Fn(fn) => `Fn(fn)
  };

let promiseReject: string => Js.Promise.t(Js.Promise.error) = [%raw
  str => "return Promise.reject(str)"
];

[@bs.scope "fetch"] [@bs.val] external resetMocks: unit => unit = "resetMocks";

[@bs.scope "fetch"] [@bs.val]
external enableMocks: unit => unit = "enableMocks";

[@bs.scope "fetch"] [@bs.val]
external disableMocks: unit => unit = "disableMocks";

[@bs.scope "fetch"] [@bs.val] external mockAbort: unit => unit = "mockAbort";

[@bs.scope "fetch"] [@bs.val]
external mockAbortOnce: unit => unit = "mockAbortOnce";

[@bs.scope "fetch"] [@bs.val]
external rawMockResponse:
  (
    [@bs.unwrap] [ | `Str(string) | `Fn(unit => Js.Promise.t(string))],
    option(init)
  ) =>
  unit =
  "mockResponse";

let mockResponse = (~response: response, ~init: option(init)=?, ()) =>
  rawMockResponse(responseToParameter(response), init);

[@bs.scope "fetch"] [@bs.val]
external rawMockResponseOnce:
  (
    [@bs.unwrap] [ | `Str(string) | `Fn(unit => Js.Promise.t(string))],
    option(init)
  ) =>
  unit =
  "mockResponseOnce";

let mockResponseOnce = (~response: response, ~init: option(init)=?, ()) =>
  rawMockResponseOnce(responseToParameter(response), init);

let once = mockResponseOnce;

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesStr: array((string, Js.Undefined.t(init))) => unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesFn:
  array((unit => Js.Promise.t(string), Js.Undefined.t(init))) => unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val]
external rawMockReject:
  (
  [@bs.unwrap]
  [ | `Str(string) | `Fn(unit => Js.Promise.t(Js.Promise.error))]
  ) =>
  unit =
  "mockReject";

let mockReject = reject =>
  switch (reject) {
  | Str(str) => rawMockReject(`Str(str))
  | Fn(fn) =>
    rawMockReject(`Fn(() => fn() |> Js.Promise.then_(promiseReject)))
  };

[@bs.scope "fetch"] [@bs.val]
external rawMockRejectOnce:
  (
  [@bs.unwrap]
  [ | `Str(string) | `Fn(unit => Js.Promise.t(Js.Promise.error))]
  ) =>
  unit =
  "mockRejectOnce";

let mockRejectOnce = reject =>
  switch (reject) {
  | Str(str) => rawMockRejectOnce(`Str(str))
  | Fn(fn) =>
    rawMockRejectOnce(`Fn(() => fn() |> Js.Promise.then_(promiseReject)))
  };
