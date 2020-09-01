module CookieConsent = {
  [@bs.module "react-cookie-consent"] [@react.component]
  external make:
    (
      ~acceptOnScroll: bool=?,
      ~disableStyles: bool=?,
      ~containerClasses: string=?,
      ~buttonClasses: string=?,
      ~contentClasses: string=?,
      ~buttonText: React.element=?, //TODO: make this take either react element or string
      ~children: React.element
    ) =>
    React.element =
    "default";
};

module Styles = {
  open Css;

  let container =
    style([
      position(`fixed),
      padding2(~v=`rem(1.5), ~h=`rem(1.)),
      alignItems(`flexStart),
      justifyContent(`flexStart),
      display(`flex),
      flexDirection(`column),
      width(`percent(100.)),
      background(Theme.Colors.black),
      boxSizing(`borderBox),
      media(
        Theme.MediaQuery.notMobile,
        [
          flexDirection(`row),
          justifyContent(`spaceBetween),
          padding2(~v=`rem(3.), ~h=`rem(2.)),
        ],
      ),
    ]);

  let content =
    merge([
      Theme.Type.pageSubhead,
      style([
        color(white),
        margin2(~v=`rem(1.5), ~h=`rem(0.)),
        media(
          Theme.MediaQuery.tablet,
          [margin2(~v=`rem(1.), ~h=`rem(5.))],
        ),
      ]),
    ]);

  let button =
    merge([
      Button.Styles.button(
        Theme.Colors.mint,
        true,
        `rem(3.25),
        `rem(7.75),
        1.5,
        1.,
      ),
      style([
        color(Theme.Colors.black),
        marginRight(`auto),
        media(Theme.MediaQuery.tablet, [marginRight(`rem(2.))]),
        media(Theme.MediaQuery.desktop, [marginRight(`rem(4.))]),
      ]),
    ]);

  let text =
    style([
      display(`block),
      marginRight(`rem(2.)),
      media(
        Theme.MediaQuery.tablet,
        [display(`flex), flexDirection(`column)],
      ),
    ]);

  let buttonText =
    style([
      display(`flex),
      justifyContent(`spaceAround),
      alignItems(`center),
    ]);

  let buttonIcon =
    style([display(`flex), alignItems(`center), marginLeft(`rem(0.5))]);
};

[@react.component]
let make = () => {
  let buttonText =
    <div className=Styles.buttonText>
      <span> {React.string("Accept")} </span>
      <span className=Styles.buttonIcon>
        <Icon kind=Icon.ArrowRightMedium />
      </span>
    </div>;

  <CookieConsent
    acceptOnScroll=true
    disableStyles=true
    containerClasses=Styles.container
    contentClasses=Styles.content
    buttonText
    buttonClasses=Styles.button>
    <div className=Styles.text>
      <span>
        {React.string(
           "We use cookies to improve your experience on our site.",
         )}
      </span>
      <span>
        <span> {React.string(" Read our")} </span>
        //TODO: Link to privacy policy
        <Next.Link href="/">
          <span
            className=Css.(
              style([color(Theme.Colors.orange), cursor(`pointer)])
            )>
            {React.string(" privacy policy ")}
          </span>
        </Next.Link>
        <span> {React.string("for more information.")} </span>
      </span>
    </div>
  </CookieConsent>;
};
