type response =
  | Str(string)
  | Fn(unit => Js.Promise.t(string));

type init = {
  status: int,
  statusText: string,
  headers: Js.Dict.t(string),
};

let responseToParameter = response =>
  switch (response) {
  | Str(str) => `Str(str)
  | Fn(fn) => `Fn(fn)
  };

[@bs.scope "fetch"] [@bs.val] external resetMocks: unit => unit = "resetMocks";

[@bs.scope "fetch"] [@bs.val]
external enableMocks: unit => unit = "enableMocks";

[@bs.scope "fetch"] [@bs.val]
external disableMocks: unit => unit = "disableMocks";

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

[@bs.scope "fetch"] [@bs.val]
external mockResponses: array('a) => unit = "mockResponses";
