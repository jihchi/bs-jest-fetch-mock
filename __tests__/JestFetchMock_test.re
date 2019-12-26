open Jest;
open Expect;
open JestFetchMock;
open Fetch;
open Js.Promise;

external unsafeErrorToString: Js.Promise.error => string = "%identity";

beforeEach(() => resetMocks());

describe("mockResponse", () => {
  testPromise("accept a string", () => {
    let expected = {|{ "body": "is a JSON string" }|};
    mockResponse(~response=Str(expected), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a string and init", () => {
    let expected = {|{ "body": "is a JSON string" }|};
    mockResponse(
      ~response=Str(expected),
      ~init=
        init(
          ~status=204,
          ~statusText="nothing for you",
          ~headers=Js.Dict.fromList([("Authorization", "Bearer <token>")]),
          (),
        ),
      (),
    );

    fetch("http://does_not_matter")
    |> then_(resp =>
         all4((
           Response.text(resp),
           Response.status(resp)->resolve,
           Response.statusText(resp)->resolve,
           Response.headers(resp)
           ->Headers.get("Authorization", _)
           ->Belt.Option.getExn
           ->resolve,
         ))
       )
    |> then_(resp =>
         resp
         |> expect
         |> toEqual((expected, 204, "nothing for you", "Bearer <token>"))
         |> resolve
       );
  });

  testPromise("accept a function", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};
    mockResponse(~response=Fn(_req => resolve(expected)), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("take request as a argument", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};
    mockResponse(
      ~response=
        Fn(
          req =>
            Fetch.Request.url(req) == "http://does_matter/"
              ? resolve(expected) : resolve(""),
        ),
      (),
    );

    fetch("http://does_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });
});

describe("mockResponseOnce", () => {
  testPromise("accept a string", () => {
    let expected = {|{ "body": "is a JSON string" }|};
    mockResponseOnce(~response=Str(expected), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a function", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};
    mockResponseOnce(~response=Fn(_req => resolve(expected)), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });
});

describe("once", () => {
  testPromise("accept a string", () => {
    let expected = {|{ "body": "is a JSON string" }|};
    once(~response=Str(expected), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a function", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};
    once(~response=Fn(_req => resolve(expected)), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });
});

describe("mockResponses", () => {
  testPromise("accept array of string", () => {
    let expected = [|
      {|{ "body_1": "is a JSON string" }|},
      {|{ "body_2": "is a JSON string" }|},
    |];
    mockResponsesStr([|
      (expected[0], Js.Undefined.empty),
      (expected[1], Js.Undefined.empty),
    |]);

    all2((
      fetch("http://does_not_matter_1") |> then_(Response.text),
      fetch("http://does_not_matter_2") |> then_(Response.text),
    ))
    |> then_(resp =>
         resp |> expect |> toEqual((expected[0], expected[1])) |> resolve
       );
  });

  testPromise("accept array of function", () => {
    let expected = [|
      {|{ "body_1": "is a JSON string from a function" }|},
      {|{ "body_2": "is a JSON string from a function" }|},
    |];
    mockResponsesFn([|
      (_req => resolve(expected[0]), Js.Undefined.empty),
      (_req => resolve(expected[1]), Js.Undefined.empty),
    |]);

    all2((
      fetch("http://does_not_matter_1") |> then_(Response.text),
      fetch("http://does_not_matter_2") |> then_(Response.text),
    ))
    |> then_(resp =>
         resp |> expect |> toEqual((expected[0], expected[1])) |> resolve
       );
  });
});

describe("mockReject", () => {
  testPromise("accept a string", () => {
    let expected = "oops";
    mockReject(Str(expected));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });

  testPromise("accept a function", () => {
    let expected = "oops";
    mockReject(Fn(_req => expected->resolve));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });
});

describe("mockRejectOnce", () => {
  testPromise("accept a string", () => {
    let expected = "oops";
    mockRejectOnce(Str(expected));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });

  testPromise("accept a function", () => {
    let expected = "oops";
    mockRejectOnce(Fn(_req => expected->resolve));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });
});
