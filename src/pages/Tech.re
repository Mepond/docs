module Styles = {
  open Css;

  let section =
    style([
      width(`rem(71.)),
      margin2(~v=`auto, ~h=`auto),
      paddingTop(`rem(3.)),
      paddingLeft(`rem(16.)),
      backgroundPosition(`rem(-6.5), `rem(-2.)),
      gridTemplateColumns([`em(14.), `auto]),
      selector("> aside", [gridColumnStart(1)]),
      selector("> :not(aside)", [gridColumnStart(2)]),
      selector("img", [width(`percent(100.))]),
    ]);

  let sideNav = sticky =>
    style([
      position(sticky ? `fixed : `absolute),
      top(sticky ? `rem(3.5) : `rem(66.)),
      marginLeft(`calc((`sub, `vw(50.), `rem(71. /. 2.)))),
      width(`rem(14.)),
      background(white),
    ]);

  let projects =
    style([
      background(`url("/static/img/tech-projects-bg.png")),
      // For some reason `auto doesn't count as a Css.length so...
      unsafe("background-size", "100% auto"),
      backgroundRepeat(`noRepeat),
      paddingTop(`rem(8.)),
    ]);

  let projectContainer =
    style([
      display(`flex),
      alignItems(`center),
      selector("img", [width(`rem(23.)), marginRight(`rem(2.))]),
    ]);

  let possibilities =
    style([
      display(`grid),
      gridTemplateColumns([`fr(1.), `fr(1.), `fr(1.)]),
      gridGap(`rem(1.)),
    ]);

  let divider =
    style([
      maxWidth(`rem(71.)),
      margin2(~v=`zero, ~h=`auto),
      height(`px(1)),
      backgroundColor(Theme.Colors.digitalBlack),
    ]);

  let actionLink =
    merge([
      Theme.Type.link,
      style([display(`inlineFlex), alignItems(`center)]),
    ]);
};

module Section = {
  [@react.component]
  let make = (~title, ~subhead, ~slug, ~children) => {
    <section className=Styles.section id=slug>
      <h2 className=Theme.Type.h2> {React.string(title)} </h2>
      <Spacer height=1.5 />
      <p className=Theme.Type.sectionSubhead> {React.string(subhead)} </p>
      <Spacer height=4. />
      children
      <Spacer height=6.5 />
    </section>;
  };
};

module TechSideNav = {
  [@react.component]
  let make = () => {
    let router = Next.Router.useRouter();
    let hashExp = Js.Re.fromString("#(.+)");
    let scrollTop = Hooks.useScroll();
    let calcHash = path =>
      Js.Re.(exec_(hashExp, path) |> Option.map(captures))
      |> Js.Option.andThen((. res) => Js.Nullable.toOption(res[0]))
      |> Js.Option.getWithDefault("");
    let (hash, setHash) = React.useState(() => calcHash(router.asPath));

    React.useEffect(() => {
      let handleRouteChange = url => setHash(_ => calcHash(url));
      router.events
      ->Next.Router.Events.on("hashChangeStart", handleRouteChange);
      Some(
        () =>
          router.events
          ->Next.Router.Events.off("hashChangeStart", handleRouteChange),
      );
    });

    <SideNav currentSlug=hash className={Styles.sideNav(scrollTop > 1000)}>
      <SideNav.Item title="How Mina Works" slug="#how-mina-works" />
      <SideNav.Item title="Projects & Possibilities" slug="#projects" />
      <SideNav.Item title="Incentive Structure" slug="#incentives" />
      <SideNav.Item title="Where We're Headed" slug="#roadmap" />
      <SideNav.Item title="Knowledge Base" slug="#knowledge" />
    </SideNav>;
  };
};

module HowMinaWorks = {
  [@react.component]
  let make = () => {
    <Section
      title="How Mina Works"
      subhead={js|Mina is a layer one protocol designed to deliver on the original promise of blockchain — true decentralization, scale and security.|js}
      slug="how-mina-works">
      <img
        src="/static/img/how-mina-works-mirrors.jpg"
        height="563"
        alt="A series of mirrors reflecting each other ad infinitum."
      />
      <Spacer height=4. />
      <p className=Theme.Type.paragraph>
        <b>
          {React.string(
             "In theory, blockchains are designed to be held accountable by its users.",
           )}
        </b>
        {React.string(
           {js|
            When anyone can enforce the rules by validating an irrevocable public
            ledger — power remains in the hands of the many, not the few. This
            decentralized structure is what allows the network to conduct trustless
            transactions.
          |js},
         )}
      </p>
      <Spacer height=1.5 />
      <p className=Theme.Type.paragraph>
        <b>
          {React.string({js|But in practice, this hasn’t been the case.|js})}
        </b>
        {React.string(
           {js|
             With legacy blockchains like Bitcoin and Ethereum, when a new participant
             joins, they have to check every transaction since the beginning of the
             network to verify correctness — which amounts to hundreds of gigabytes of
             data. Most people can’t afford the computing power it takes to verify these
             heavy chains on their own and are forced  to trust increasingly powerful
             intermediaries. This means most folks can no longer connect peer-to-peer
             — causing decentralization to suffer, power dynamics to shift, and the
             network to become more vulnerable to censorship.
          |js},
         )}
      </p>
      <Spacer height=1.5 />
      <p className=Theme.Type.paragraph>
        <b>
          {React.string(
             {js|
               Mina offers an elegant solution: replacing the blockchain with an
               easily verifiable, consistent-sized cryptographic proof.
             |js},
           )}
        </b>
        {React.string(
           {js|
             Mina dramatically reduces the amount of data each user needs to download.
             Instead of verifying the entire chain from the beginning of time,
             participants fully verify the network and transactions using recursive
             zero knowledge proofs (or zk-SNARKs). Nodes can then store just this proof,
             as opposed to the entire chain. And because it’s a consistent size, Mina
             stays accessible and can be trustlessly accessed from any device — even
             as it scales to millions of users and accumulates years of transaction data.
          |js},
         )}
      </p>
      <Spacer height=4. />
      // TODO replace with final animation
      <img
        src="/static/img/how-mina-works-mirrors.jpg"
        height="563"
        alt="A series of mirrors reflecting each other ad infinitum."
      />
      <Spacer height=4. />
      <p className=Theme.Type.paragraph>
        <b> {React.string("But how do zk-SNARKs work?")} </b>
        {React.string(
           {js|
            They capture the state of the entire blockchain as a lightweight snapshot
            and send that around — instead of the chain itself. It’s like sending your
            friend a postcard of an elephant, instead of a massive live animal. When
            the next block in the network is created, it takes a snapshot of itself
            — with the snapshot of the previous state of the blockchain as the background.
            That new snapshot will in turn be used as the backdrop for the next block,
            and so on and so on. Rather amazingly, while it can contain proof of an
            infinite amount of information, the snapshot always remains the same size.
          |js},
         )}
      </p>
      <Spacer height=1.5 />
      <p className=Theme.Type.paragraph>
        <b>
          {React.string(
             {js|
               Coming full circle, the world’s lightest blockchain empowers inclusive consensus.
             |js},
           )}
        </b>
        {React.string(
           {js|
             Our modified Ouroboros proof-of-stake protocol maximizes inclusivity in
             consensus. On Mina, all participants act as full nodes and anyone can take
             part in consensus, secure the blockchain and hold Mina accountable.
          |js},
         )}
      </p>
      <Spacer height=1.5 />
      <p className=Theme.Type.paragraph>
        <b>
          {React.string(
             {js|
               And that’s how Mina will deliver true decentralization, scale and security.
             |js},
           )}
        </b>
      </p>
    </Section>;
  };
};

<<<<<<< HEAD
module Projects = {
  module ProjectCopy = {
    [@react.component]
    let make = (~title, ~description, ~url) =>
      <div>
        <h4 className=Theme.Type.h4> {React.string(title)} </h4>
        <Spacer height=0.5 />
        <p className=Theme.Type.paragraph> {React.string(description)} </p>
        <Spacer height=0.5 />
        <a href=url className=Styles.actionLink>
          <span className=Theme.Type.link>
            {React.string("See it in Action")}
          </span>
          <Icon size=1.5 kind=Icon.ExternalLink />
        </a>
      </div>;
  };

  module Possibility = {
    [@react.component]
    let make = (~title, ~description, ~image) =>
      <div>
        <img src=image />
        <Spacer height=1. />
        <h4 className=Theme.Type.h4> {React.string(title)} </h4>
        <Spacer height=0.5 />
        <p className=Theme.Type.paragraph> {React.string(description)} </p>
      </div>;
  };

  [@react.component]
  let make = () =>
    <div className=Styles.projects>
      <Section
        title="Projects & Possibilities"
        subhead={js|Developers are already building powerful applications on Mina — but this is just the beginning.|js}
        slug="projects">
        <hr className=Styles.divider />
        <Spacer height=1. />
        <h3 className=Theme.Type.h3> {React.string("Built on Mina")} </h3>
        <Spacer height=3. />
        <img src="/static/img/AboutHeroTabletBackground.jpg" />
        <Spacer height=2. />
        <ProjectCopy
          title="Figment Block Explorer"
          description="This open source Mina block explorer provides aggregated network data to enable users to view transactions, blocks, and accounts."
          url="/"
        />
        <Spacer height=2. />
        <div className=Styles.projectContainer>
          <img src="/static/img/AboutHeroTabletBackground.jpg" />
          <ProjectCopy
            title="Mina Mobile Wallet"
            description={js|This wallet gives users full access to Mina tokens on their phone — so they can transact any time, anywhere.|js}
            url="/"
          />
        </div>
        <Spacer height=2. />
        <div className=Styles.projectContainer>
          <img src="/static/img/AboutHeroTabletBackground.jpg" />
          <ProjectCopy
            title="Faucet Bot"
            description="Built on Mina and integrated with Discord, this tool automatically distributes Mina tokens to participants who need them for Testnet challenges and activities."
            url="/"
          />
        </div>
        <Spacer height=4. />
        <hr className=Styles.divider />
        <Spacer height=1. />
        <h3 className=Theme.Type.h3>
          {React.string("Explore the Possiblities")}
        </h3>
        <Spacer height=3. />
        <div className=Styles.possibilities>
          <Possibility
            title="Build Snapps: Privacy-Enabled apps"
            description="Leverage Mina to develop decentralized apps that use zk-SNARKs to ensure privacy, without exposing users’ data to a public blockchain."
            image="/static/img/AboutHeroTabletBackground.jpg"
          />
          <Possibility
            title="Build Snapps: Privacy-Enabled apps"
            description="Leverage Mina to develop decentralized apps that use zk-SNARKs to ensure privacy, without exposing users’ data to a public blockchain."
            image="/static/img/AboutHeroTabletBackground.jpg"
          />
          <Possibility
            title="Build Snapps: Privacy-Enabled apps"
            description="Leverage Mina to develop decentralized apps that use zk-SNARKs to ensure privacy, without exposing users’ data to a public blockchain."
            image="/static/img/AboutHeroTabletBackground.jpg"
          />
          <Possibility
            title="Build Snapps: Privacy-Enabled apps"
            description="Leverage Mina to develop decentralized apps that use zk-SNARKs to ensure privacy, without exposing users’ data to a public blockchain."
            image="/static/img/AboutHeroTabletBackground.jpg"
          />
          <Possibility
            title="Build Snapps: Privacy-Enabled apps"
            description="Leverage Mina to develop decentralized apps that use zk-SNARKs to ensure privacy, without exposing users’ data to a public blockchain."
            image="/static/img/AboutHeroTabletBackground.jpg"
          />
          <Possibility
            title="Build Snapps: Privacy-Enabled apps"
            description="Leverage Mina to develop decentralized apps that use zk-SNARKs to ensure privacy, without exposing users’ data to a public blockchain."
            image="/static/img/AboutHeroTabletBackground.jpg"
          />
        </div>
      </Section>
    </div>;
};

module Incentives = {
  module Incentive = {
    [@react.component]
    let make = (~title, ~description, ~image, ~url) =>
      <div className=Styles.projectContainer>
        <img src=image />
        <div>
          <h4 className=Theme.Type.h4> {React.string(title)} </h4>
          <Spacer height=0.5 />
          <p className=Theme.Type.paragraph> {React.string(description)} </p>
          <Spacer height=0.5 />
          <a href=url className=Styles.actionLink>
            <span className=Theme.Type.link>
              {React.string("Run a Node")}
            </span>
            <Icon size=1.5 kind=Icon.ArrowRightLarge />
          </a>
        </div>
      </div>;
  };

  [@react.component]
  let make = () =>
    <Section
      title="Incentive Structure"
      subhead="From its protocol architecture and roles framework to its incentive structure and monetary policy, Mina is designed to maximize network scalability and security."
      slug="incentives">
      <Button width={`rem(15.25)}>
        {React.string("Economics Whitepaper")}
        <Icon kind=Icon.ArrowRightSmall />
      </Button>
      <Spacer height=4. />
      <hr className=Styles.divider />
      <Spacer height=2. />
      <h3 className=Theme.Type.h3> {React.string("Ways to Earn Mina")} </h3>
      <Spacer height=2. />
      <p className=Theme.Type.sectionSubhead>
        {React.string(
           "Mina is breaking down barriers to participation and unleashing a host of exciting new pathways to earn tokens.",
         )}
      </p>
      <Spacer height=3. />
      <Incentive
        title="As a Block Producer"
        description="Block producers are akin to miners or stakers in other protocols. By staking Mina, they can be selected to produce a block and earn block rewards in the form of coinbase, transaction fees and network fees. Block producers can decide to also be SNARK producers."
        image="/static/img/tech-block-producer.png"
        url="/"
      />
      <Spacer height=3. />
      <Incentive
        title="As a Snark Producer"
        description="The second type of consensus node operator on Mina, snark producers help compress data in the network by generating SNARK proofs of transactions. They then sell those proofs to block producers in return for a portion of the block rewards."
        image="/static/img/tech-snark-producer.png"
        url="/"
      />
      <Spacer height=3. />
      <Incentive
        title="As a Professional Block Producer"
        description="Because staking requires nodes to be online, some may choose to delegate their Mina to staking pools. These groups run staking services in exchange for a fee, which is automatically deducted when the delegator gets selected to be a block producer."
        image="/static/img/tech-pro-delegator.png"
        url="/"
      />
    </Section>;
};

[@react.component]
let make = () => {
  <Page title="Mina Cryptocurrency Protocol" footerColor=Theme.Colors.orange>
    <div className=Nav.Styles.spacer />
    <Hero
      background={
        Theme.desktop: "/static/img/tech-hero-desktop.jpg",
        Theme.tablet: "/static/img/AboutHeroTabletBackground.jpg",
        Theme.mobile: "/static/img/AboutHeroMobileBackground.jpg",
      }
      title="Tech"
      header="An Elegant Solution"
      copy="Rather than apply brute computing force, Mina uses advanced cryptography and recursive zk-SNARKs to deliver true decentralization at scale."
    />
    <TechSideNav />
    <Spacer height=6.5 />
    <hr className=Styles.divider />
    <HowMinaWorks />
    <Projects />
    <Spacer height=1.5 />
    <hr className=Styles.divider />
    <Incentives />
    <Spacer height=1.5 />
    <div className=Styles.projects>
      <Section
        title="Mina Milestones and the Road Ahead"
        subhead={js|
          We’re proud of what we’ve accomplished with our community so far — and
          look forward to tackling challenges and building more with a whole new
          generation of participants.
        |js}
        slug="roadmap">
        <img src="/static/img/tech-roadmap.svg" width="100%" />
      </Section>
      <Spacer height=7. />
    </div>
    <FeaturedSingleRow
      row={
        rowType: FeaturedSingleRow.Row.ImageRightCopyLeft,
        title: "Get Started",
        description: {js|
          We’re passionate about making it as simple as possible to participate
          in Mina. With clear documentation, a supportive community and a chain
          that syncs in seconds, we’ll get you up and running in record time.
        |js},
        textColor: `currentColor,
        image: "/static/img/skateboard.jpg",
        background: Image("/static/img/skateboard.jpg"),
        button: {
          buttonColor: Theme.Colors.orange,
          buttonTextColor: Css.white,
          buttonText: "Run a Node",
          dark: false,
        },
        contentBackground: Color(Css.white),
      }
    />
    <Spacer height=6. />
    <div className=Styles.section id="knowledge">
      <h2 className=Theme.Type.h2>
        {React.string("Knowledge Base")}
      </h2>
    </div>
    <Spacer height=12. />
    <FeaturedSingleRow
      row={
        rowType: FeaturedSingleRow.Row.ImageLeftCopyRight,
        title: "Get Started",
        description: {js|
          We’re passionate about making it as simple as possible to participate
          in Mina. With clear documentation, a supportive community and a chain
          that syncs in seconds, we’ll get you up and running in record time.
        |js},
        textColor: `currentColor,
        image: "/static/img/skateboard.jpg",
        background: Image("/static/img/skateboard.jpg"),
        button: {
          buttonColor: Theme.Colors.orange,
          buttonTextColor: Css.white,
          buttonText: "Run a Node",
          dark: false,
        },
        contentBackground: Color(Css.white),
      }
    />
  </Page>;
};
