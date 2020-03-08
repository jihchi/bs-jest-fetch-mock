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

    mockResponse(`Str(expected), Js.Undefined.empty);

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a string and init", () => {
    let expected = {|{ "body": "is a JSON string" }|};

    mockResponse(
      `Str(expected),
      Js.Undefined.return(
        requestInit(
          ~status=204,
          ~statusText="nothing for you",
          ~headers=Js.Dict.fromList([("Authorization", "Bearer <token>")]),
          (),
        ),
      ),
    );

    fetch("http://does_not_matter")
    |> then_(resp =>
         all4((
           resp |> Response.text,
           resp |> Response.status |> resolve,
           resp |> Response.statusText |> resolve,
           resp
           |> Response.headers
           |> Headers.get("Authorization")
           |> Belt.Option.getExn
           |> resolve,
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

    mockResponse(`FnStr(_req => resolve(expected)), Js.Undefined.empty);

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("take request as a argument", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};

    mockResponse(
      `FnStr(
        req =>
          if (Fetch.Request.url(req) == "http://does_matter/") {
            resolve(expected);
          } else {
            resolve("");
          },
      ),
      Js.Undefined.empty,
    );

    fetch("http://does_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });
});

describe("mockResponseOnce", () => {
  testPromise("accept a string", () => {
    let expected = {|{ "body": "is a JSON string" }|};

    mockResponseOnce(`Str(expected), Js.Undefined.empty);

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a function", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};

    mockResponseOnce(`FnStr(_req => resolve(expected)), Js.Undefined.empty);

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });
});

describe("once", () => {
  testPromise("accept a string", () => {
    let expected = {|{ "body": "is a JSON string" }|};

    once(`Str(expected), Js.Undefined.empty);

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a function", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};

    once(`FnStr(_req => resolve(expected)), Js.Undefined.empty);

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });
});

describe("mockResponses", () => {
  testPromise("accept array of string", () => {
    let expected1 = {|{ "body_1": "is a JSON string" }|};
    let expected2 = {|{ "body_2": "is a JSON string" }|};

    mockResponsesStr([|
      (expected1, Js.Undefined.empty),
      (expected2, Js.Undefined.empty),
    |]);

    all2((
      fetch("http://does_not_matter_1") |> then_(Response.text),
      fetch("http://does_not_matter_2") |> then_(Response.text),
    ))
    |> then_(resp =>
         resp |> expect |> toEqual((expected1, expected2)) |> resolve
       );
  });

  testPromise("accept array of function", () => {
    let expected1 = {|{ "body_1": "is a JSON string from a function" }|};
    let expected2 = {|{ "body_2": "is a JSON string from a function" }|};

    mockResponsesFn([|
      (_req => resolve(expected1), Js.Undefined.empty),
      (_req => resolve(expected2), Js.Undefined.empty),
    |]);

    all2((
      fetch("http://does_not_matter_1") |> then_(Response.text),
      fetch("http://does_not_matter_2") |> then_(Response.text),
    ))
    |> then_(resp =>
         resp |> expect |> toEqual((expected1, expected2)) |> resolve
       );
  });
});

describe("mockReject", () => {
  testPromise("accept a string", () => {
    let expected = "oops";

    mockReject(`Str(expected));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });

  testPromise("accept a function", () => {
    let expected = "oops";

    mockReject(`FnStr(_req => expected |> Js.Exn.raiseError |> reject));

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

    mockRejectOnce(`Str(expected));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });

  testPromise("accept a function", () => {
    let expected = "oops";

    mockRejectOnce(`FnStr(_req => expected |> Js.Exn.raiseError |> resolve));

    fetch("http://does_not_matter")
    |> then_(_ => fail("should get rejected") |> resolve)
    |> catch(resp =>
         resp |> unsafeErrorToString |> expect |> toEqual(expected) |> resolve
       );
  });
});
