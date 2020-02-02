type impl = [ | `Fn(Fetch.request => Js.Promise.t(string)) | `Str(string)];

[@bs.deriving abstract]
type init = {
  [@bs.optional]
  status: int,
  [@bs.optional]
  statusText: string,
  [@bs.optional]
  headers: Js.Dict.t(string),
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
    [@bs.unwrap] [
      | `Str(string)
      | `Fn(Fetch.request => Js.Promise.t(string))
    ],
    option(init)
  ) =>
  unit =
  "mockResponse";

let mockResponse = (~response: impl, ~init: option(init)=?, ()) =>
  rawMockResponse(response, init);

[@bs.scope "fetch"] [@bs.val]
external rawMockResponseOnce:
  (
    [@bs.unwrap] [
      | `Str(string)
      | `Fn(Fetch.request => Js.Promise.t(string))
    ],
    option(init)
  ) =>
  unit =
  "mockResponseOnce";

let mockResponseOnce = (~response: impl, ~init: option(init)=?, ()) =>
  rawMockResponseOnce(response, init);

let once = mockResponseOnce;

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesStr: array((string, Js.Undefined.t(init))) => unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesFn:
  array((Fetch.request => Js.Promise.t(string), Js.Undefined.t(init))) =>
  unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val]
external rawMockReject:
  (
  [@bs.unwrap]
  [ | `Str(string) | `Fn(Fetch.request => Js.Promise.t(Js.Promise.error))]
  ) =>
  unit =
  "mockReject";

let mockReject = reject =>
  switch (reject) {
  | `Str(_str) as original => rawMockReject(original)
  | `Fn(fn) =>
    rawMockReject(`Fn(req => fn(req) |> Js.Promise.then_(promiseReject)))
  };

[@bs.scope "fetch"] [@bs.val]
external rawMockRejectOnce:
  (
  [@bs.unwrap]
  [ | `Str(string) | `Fn(Fetch.request => Js.Promise.t(Js.Promise.error))]
  ) =>
  unit =
  "mockRejectOnce";

let mockRejectOnce = reject =>
  switch (reject) {
  | `Str(_str) as original => rawMockRejectOnce(original)
  | `Fn(fn) =>
    rawMockRejectOnce(
      `Fn(req => fn(req) |> Js.Promise.then_(promiseReject)),
    )
  };
