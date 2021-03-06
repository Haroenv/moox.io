open BsReactNative;

let styles =
  StyleSheet.create(
    Style.(
      {
        "title":
          style([
            fontSize(Float(36.)),
            fontWeight(`Bold),
            textAlign(Center),
            marginVertical(Pt(20.)),
            color(String("#030303")),
          ]),
        "links":
          style([
            flexDirection(Row),
            justifyContent(Center),
            alignItems(Center),
          ]),
      }
    ),
  );

let component = ReasonReact.statelessComponent("Home");

let make = (~talks) => {
  ...component,
  render: _self =>
    <ScrollView>
      <CommonThings />
      <Head title={j|MoOx Talks, Frontend UI Web & Mobile Developer.|j} />
      <Header />
      <Container>
        <Text style=styles##title> ("Latest Talks" |> R.string) </Text>
        <Background>
          (
            switch ((talks: T.contentList)) {
            | Inactive
            | Loading => <Text> ("Loading ..." |> R.string) </Text>
            | Errored => <Text> ("Oops" |> R.string) </Text>
            | Idle(talks) =>
              <View>
                <TalkList talks=talks##list />
                <View style=styles##links>
                  (
                    switch (talks##previous |> Js.toOption) {
                    | Some(previous) =>
                      <TextLink
                        href=(
                          talks##previousPageIsFirst ?
                            "/talks/" : "/talks/after/" ++ previous ++ "/"
                        )>
                        ("Fresh talks" |> R.string)
                      </TextLink>
                    | None => R.null
                    }
                  )
                  <Text> (" " |> R.string) </Text>
                  (
                    switch (talks##next |> Js.toOption) {
                    | Some(next) =>
                      <TextLink href=("/talks/after/" ++ next ++ "/")>
                        ("Older talks" |> R.string)
                      </TextLink>
                    | None => R.null
                    }
                  )
                </View>
              </View>
            }
          )
        </Background>
      </Container>
      <Footer />
    </ScrollView>,
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~talks=PhenomicPresetReactApp.jsEdge(jsProps##talks))
  );

let queries = props => {
  let talks =
    PhenomicPresetReactApp.query(
      PaginatedList({
        path: "content/talks",
        by: Some("default"),
        value: None,
        order: None,
        sort: None,
        limit: Some(10),
        after: Some(props##params##after),
      }),
    );
  {"talks": talks};
};
