open Jest;
open Expect;
open JestFetchMock;
open Fetch;
open Js.Promise;

beforeEach(() => resetMocks());

describe("mockResponse", () => {
  testPromise("accept a string", () => {
    let expected = {|{ "body": "is a JSON string" }|};
    mockResponse(~response=Str(expected), ());

    fetch("http://does_not_matter")
    |> then_(Response.text)
    |> then_(resp => resp |> expect |> toEqual(expected) |> resolve);
  });

  testPromise("accept a function", () => {
    let expected = {|{ "body": "is a JSON string from a function" }|};
    mockResponse(~response=Fn(() => resolve(expected)), ());

    fetch("http://does_not_matter")
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
    mockResponseOnce(~response=Fn(() => resolve(expected)), ());

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
    once(~response=Fn(() => resolve(expected)), ());

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
      (() => resolve(expected[0]), Js.Undefined.empty),
      (() => resolve(expected[1]), Js.Undefined.empty),
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
