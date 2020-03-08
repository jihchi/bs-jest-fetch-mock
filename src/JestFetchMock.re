[@bs.deriving abstract]
type requestInit = {
  [@bs.optional]
  status: int,
  [@bs.optional]
  statusText: string,
  [@bs.optional]
  headers: Js.Dict.t(string),
};

[@bs.deriving abstract]
type responseInit = {
  [@bs.optional]
  status: int,
  [@bs.optional]
  statusText: string,
  [@bs.optional]
  headers: Js.Dict.t(string),
  body: string,
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
external mockResponse:
  (
    [@bs.unwrap] [
      | `FnStr(Fetch.request => Js.Promise.t(string))
      | `FnResp(Fetch.request => Js.Promise.t(responseInit))
      | `Str(string)
    ],
    Js.Undefined.t(requestInit)
  ) =>
  unit =
  "mockResponse";

[@bs.scope "fetch"] [@bs.val]
external mockResponseOnce:
  (
    [@bs.unwrap] [
      | `FnStr(Fetch.request => Js.Promise.t(string))
      | `FnResp(Fetch.request => Js.Promise.t(responseInit))
      | `Str(string)
    ],
    Js.Undefined.t(requestInit)
  ) =>
  unit =
  "mockResponseOnce";

let once = mockResponseOnce;

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesStr:
  array((string, Js.Undefined.t(requestInit))) => unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesFn:
  array(
    (Fetch.request => Js.Promise.t(string), Js.Undefined.t(requestInit)),
  ) =>
  unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val] [@bs.variadic]
external mockResponsesFnResp:
  array(
    (
      Fetch.request => Js.Promise.t(responseInit),
      Js.Undefined.t(requestInit),
    ),
  ) =>
  unit =
  "mockResponses";

[@bs.scope "fetch"] [@bs.val]
external mockReject:
  (
  [@bs.unwrap]
  [
    | `Str(string)
    | `FnStr(Fetch.request => Js.Promise.t(Js.Promise.error))
  ]
  ) =>
  unit =
  "mockReject";

[@bs.scope "fetch"] [@bs.val]
external mockRejectOnce:
  (
  [@bs.unwrap]
  [
    | `Str(string)
    | `FnStr(Fetch.request => Js.Promise.t(Js.Promise.error))
  ]
  ) =>
  unit =
  "mockRejectOnce";
