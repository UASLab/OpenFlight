





<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
  <link rel="dns-prefetch" href="https://assets-cdn.github.com">
  <link rel="dns-prefetch" href="https://avatars0.githubusercontent.com">
  <link rel="dns-prefetch" href="https://avatars1.githubusercontent.com">
  <link rel="dns-prefetch" href="https://avatars2.githubusercontent.com">
  <link rel="dns-prefetch" href="https://avatars3.githubusercontent.com">
  <link rel="dns-prefetch" href="https://github-cloud.s3.amazonaws.com">
  <link rel="dns-prefetch" href="https://user-images.githubusercontent.com/">



  <link crossorigin="anonymous" href="https://assets-cdn.github.com/assets/frameworks-2d2d4c150f7000385741c6b992b302689ecd172246c6428904e0813be9bceca6.css" integrity="sha256-LS1MFQ9wADhXQca5krMCaJ7NFyJGxkKJBOCBO+m87KY=" media="all" rel="stylesheet" />
  <link crossorigin="anonymous" href="https://assets-cdn.github.com/assets/github-0522ae8d3b3bdc841d2f91f90efd5f1fd9040d910905674cd134ced43a6dfea6.css" integrity="sha256-BSKujTs73IQdL5H5Dv1fH9kEDZEJBWdM0TTO1Dpt/qY=" media="all" rel="stylesheet" />
  
  
  
  

  <meta name="viewport" content="width=device-width">
  
  <title>navigation/EKF_15state.cxx at master · AuraUAS/navigation</title>
  <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub">
  <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub">
  <meta property="fb:app_id" content="1401488693436528">

    
    <meta content="https://avatars7.githubusercontent.com/u/12717120?v=4&amp;s=400" property="og:image" /><meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="AuraUAS/navigation" property="og:title" /><meta content="https://github.com/AuraUAS/navigation" property="og:url" /><meta content="navigation - Navigation toolbox with python wrappers" property="og:description" />

  <link rel="assets" href="https://assets-cdn.github.com/">
  <link rel="web-socket" href="wss://live.github.com/_sockets/VjI6MTcyODcwNzczOjgzYmY0ZWExOTAyZTg4NDM5OTgwNTg4YWJmM2I4Nzg2YzUzMmFjODk3MjU5YWUwYmMxZjJjZTYwOTViZWYzZjQ=--9b82e160a567145c4ab188172b4285bb540a34d5">
  <meta name="pjax-timeout" content="1000">
  <link rel="sudo-modal" href="/sessions/sudo_modal">
  <meta name="request-id" content="C397:5AA0:54EA4B:95E2C2:596922C0" data-pjax-transient>
  

  <meta name="selected-link" value="repo_source" data-pjax-transient>

  <meta name="google-site-verification" content="KT5gs8h0wvaagLKAVWq8bbeNwnZZK1r1XQysX3xurLU">
<meta name="google-site-verification" content="ZzhVyEFwb7w3e0-uOTltm8Jsck2F5StVihD0exw2fsA">
    <meta name="google-analytics" content="UA-3769691-2">

<meta content="collector.githubapp.com" name="octolytics-host" /><meta content="github" name="octolytics-app-id" /><meta content="https://collector.githubapp.com/github-external/browser_event" name="octolytics-event-url" /><meta content="C397:5AA0:54EA4B:95E2C2:596922C0" name="octolytics-dimension-request_id" /><meta content="iad" name="octolytics-dimension-region_edge" /><meta content="iad" name="octolytics-dimension-region_render" /><meta content="11790190" name="octolytics-actor-id" /><meta content="rega0051" name="octolytics-actor-login" /><meta content="6f5c375da68e80c07b741ceee6c9edfcfd8f99cb9743d3bde5b05412b5ef94a5" name="octolytics-actor-hash" />
<meta content="/&lt;user-name&gt;/&lt;repo-name&gt;/blob/show" data-pjax-transient="true" name="analytics-location" />




  <meta class="js-ga-set" name="dimension1" content="Logged In">


  

      <meta name="hostname" content="github.com">
  <meta name="user-login" content="rega0051">

      <meta name="expected-hostname" content="github.com">
    <meta name="js-proxy-site-detection-payload" content="ZGZlZTU5MzcwNmM3NDE2MWU4YjAyZDM0YTlkZWMzZWYyYzU3NTA4YWNjMDUzM2YwOTE1YjM0OGMzZWZhNTI1Y3x7InJlbW90ZV9hZGRyZXNzIjoiNjcuNi44Ljc2IiwicmVxdWVzdF9pZCI6IkMzOTc6NUFBMDo1NEVBNEI6OTVFMkMyOjU5NjkyMkMwIiwidGltZXN0YW1wIjoxNTAwMDYyNDA4LCJob3N0IjoiZ2l0aHViLmNvbSJ9">


  <meta name="html-safe-nonce" content="38e6ec17d9d454283ac00862e065aedc3ae7a7e3">

  <meta http-equiv="x-pjax-version" content="175e789258843bb35d9544367c73edfe">
  

      <link href="https://github.com/AuraUAS/navigation/commits/master.atom" rel="alternate" title="Recent Commits to navigation:master" type="application/atom+xml">

  <meta name="description" content="navigation - Navigation toolbox with python wrappers">
  <meta name="go-import" content="github.com/AuraUAS/navigation git https://github.com/AuraUAS/navigation.git">

  <meta content="12717120" name="octolytics-dimension-user_id" /><meta content="AuraUAS" name="octolytics-dimension-user_login" /><meta content="51852679" name="octolytics-dimension-repository_id" /><meta content="AuraUAS/navigation" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="51852679" name="octolytics-dimension-repository_network_root_id" /><meta content="AuraUAS/navigation" name="octolytics-dimension-repository_network_root_nwo" /><meta content="false" name="octolytics-dimension-repository_explore_github_marketplace_ci_cta_shown" />


    <link rel="canonical" href="https://github.com/AuraUAS/navigation/blob/master/src/nav_eigen/EKF_15state.cxx" data-pjax-transient>


  <meta name="browser-stats-url" content="https://api.github.com/_private/browser/stats">

  <meta name="browser-errors-url" content="https://api.github.com/_private/browser/errors">

  <link rel="mask-icon" href="https://assets-cdn.github.com/pinned-octocat.svg" color="#000000">
  <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico">

<meta name="theme-color" content="#1e2327">


  <meta name="u2f-support" content="true">

  </head>

  <body class="logged-in env-production page-blob">
    



  <div class="position-relative js-header-wrapper ">
    <a href="#start-of-content" tabindex="1" class="bg-black text-white p-3 show-on-focus js-skip-to-content">Skip to content</a>
    <div id="js-pjax-loader-bar" class="pjax-loader-bar"><div class="progress"></div></div>

    
    
    



        
<div class="header" role="banner">
  <div class="container clearfix">
    <a class="header-logo-invertocat" href="https://github.com/" data-hotkey="g d" aria-label="Homepage" data-ga-click="Header, go to dashboard, icon:logo">
  <svg aria-hidden="true" class="octicon octicon-mark-github" height="32" version="1.1" viewBox="0 0 16 16" width="32"><path fill-rule="evenodd" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0 0 16 8c0-4.42-3.58-8-8-8z"/></svg>
</a>


        <div class="header-search scoped-search site-scoped-search js-site-search" role="search">
  <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/AuraUAS/navigation/search" class="js-site-search-form" data-scoped-search-url="/AuraUAS/navigation/search" data-unscoped-search-url="/search" method="get"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /></div>
    <label class="form-control header-search-wrapper js-chromeless-input-container">
        <a href="/AuraUAS/navigation/blob/master/src/nav_eigen/EKF_15state.cxx" class="header-search-scope no-underline">This repository</a>
      <input type="text"
        class="form-control header-search-input js-site-search-focus js-site-search-field is-clearable"
        data-hotkey="s"
        name="q"
        value=""
        placeholder="Search"
        aria-label="Search this repository"
        data-unscoped-placeholder="Search GitHub"
        data-scoped-placeholder="Search"
        autocapitalize="off">
        <input type="hidden" class="js-site-search-type-field" name="type" >
    </label>
</form></div>


      <ul class="header-nav float-left" role="navigation">
        <li class="header-nav-item">
          <a href="/pulls" aria-label="Pull requests you created" class="js-selected-navigation-item header-nav-link" data-ga-click="Header, click, Nav menu - item:pulls context:user" data-hotkey="g p" data-selected-links="/pulls /pulls/assigned /pulls/mentioned /pulls">
            Pull requests
</a>        </li>
        <li class="header-nav-item">
          <a href="/issues" aria-label="Issues you created" class="js-selected-navigation-item header-nav-link" data-ga-click="Header, click, Nav menu - item:issues context:user" data-hotkey="g i" data-selected-links="/issues /issues/assigned /issues/mentioned /issues">
            Issues
</a>        </li>
            <li class="header-nav-item">
              <a href="/marketplace" class="js-selected-navigation-item header-nav-link" data-ga-click="Header, click, Nav menu - item:marketplace context:user" data-selected-links=" /marketplace">
                Marketplace
</a>            </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="https://gist.github.com/" data-ga-click="Header, go to gist, text:gist">Gist</a>
          </li>
      </ul>

    
<ul class="header-nav user-nav float-right" id="user-links">
  <li class="header-nav-item">
    
    <a href="/notifications" aria-label="You have unread notifications" class="header-nav-link notification-indicator tooltipped tooltipped-s js-socket-channel js-notification-indicator " data-channel="notification-changed:11790190" data-ga-click="Header, go to notifications, icon:unread" data-hotkey="g n">
        <span class="mail-status unread"></span>
        <svg aria-hidden="true" class="octicon octicon-bell float-left" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M14 12v1H0v-1l.73-.58c.77-.77.81-2.55 1.19-4.42C2.69 3.23 6 2 6 2c0-.55.45-1 1-1s1 .45 1 1c0 0 3.39 1.23 4.16 5 .38 1.88.42 3.66 1.19 4.42l.66.58H14zm-7 4c1.11 0 2-.89 2-2H5c0 1.11.89 2 2 2z"/></svg>
</a>
  </li>

  <li class="header-nav-item dropdown js-menu-container">
    <a class="header-nav-link tooltipped tooltipped-s js-menu-target" href="/new"
       aria-label="Create new…"
       aria-expanded="false"
       aria-haspopup="true"
       data-ga-click="Header, create new, icon:add">
      <svg aria-hidden="true" class="octicon octicon-plus float-left" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 9H7v5H5V9H0V7h5V2h2v5h5z"/></svg>
      <span class="dropdown-caret"></span>
    </a>

    <div class="dropdown-menu-content js-menu-content">
      <ul class="dropdown-menu dropdown-menu-sw">
        
<a class="dropdown-item" href="/new" data-ga-click="Header, create new repository">
  New repository
</a>

  <a class="dropdown-item" href="/new/import" data-ga-click="Header, import a repository">
    Import repository
  </a>

<a class="dropdown-item" href="https://gist.github.com/" data-ga-click="Header, create new gist">
  New gist
</a>

  <a class="dropdown-item" href="/organizations/new" data-ga-click="Header, create new organization">
    New organization
  </a>



  <div class="dropdown-divider"></div>
  <div class="dropdown-header">
    <span title="AuraUAS/navigation">This repository</span>
  </div>
    <a class="dropdown-item" href="/AuraUAS/navigation/issues/new" data-ga-click="Header, create new issue">
      New issue
    </a>

      </ul>
    </div>
  </li>

  <li class="header-nav-item dropdown js-menu-container">
    <a class="header-nav-link name tooltipped tooltipped-sw js-menu-target" href="/rega0051"
       aria-label="View profile and more"
       aria-expanded="false"
       aria-haspopup="true"
       data-ga-click="Header, show menu, icon:avatar">
      <img alt="@rega0051" class="avatar" src="https://avatars4.githubusercontent.com/u/11790190?v=4&amp;s=40" height="20" width="20">
      <span class="dropdown-caret"></span>
    </a>

    <div class="dropdown-menu-content js-menu-content">
      <div class="dropdown-menu dropdown-menu-sw">
        <div class="dropdown-header header-nav-current-user css-truncate">
          Signed in as <strong class="css-truncate-target">rega0051</strong>
        </div>

        <div class="dropdown-divider"></div>

        <a class="dropdown-item" href="/rega0051" data-ga-click="Header, go to profile, text:your profile">
          Your profile
        </a>
        <a class="dropdown-item" href="/rega0051?tab=stars" data-ga-click="Header, go to starred repos, text:your stars">
          Your stars
        </a>
        <a class="dropdown-item" href="/explore" data-ga-click="Header, go to explore, text:explore">
          Explore
        </a>
        <a class="dropdown-item" href="https://help.github.com" data-ga-click="Header, go to help, text:help">
          Help
        </a>

        <div class="dropdown-divider"></div>

        <a class="dropdown-item" href="/settings/profile" data-ga-click="Header, go to settings, icon:settings">
          Settings
        </a>

        <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/logout" class="logout-form" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="cP6hfohGpW204Wdc0NdS6Dkpce8WoOsoUWXggHVT4Dd7sCvU4shqmuuA+CCWP6DxfWa23kEY55aGsdpjoNIo+g==" /></div>
          <button type="submit" class="dropdown-item dropdown-signout" data-ga-click="Header, sign out, icon:logout">
            Sign out
          </button>
</form>      </div>
    </div>
  </li>
</ul>


    <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/logout" class="sr-only right-0" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="yslICozihW0UYegCP68ZRxxwexwobjgBx/hS8P2T5k3Bh8Kg5mxKmksAd355R+teWD+8LX/WNL8QLGgTKBIugA==" /></div>
      <button type="submit" class="dropdown-item dropdown-signout" data-ga-click="Header, sign out, icon:logout">
        Sign out
      </button>
</form>  </div>
</div>


      

  </div>

  <div id="start-of-content" class="show-on-focus"></div>

    <div id="js-flash-container">
</div>



  <div role="main">
        <div itemscope itemtype="http://schema.org/SoftwareSourceCode">
    <div id="js-repo-pjax-container" data-pjax-container>
      



  


    <div class="pagehead repohead instapaper_ignore readability-menu experiment-repo-nav">
      <div class="container repohead-details-container">

        <ul class="pagehead-actions">
  <li>
        <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/notifications/subscribe" class="js-social-container" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="GGsK0jJP36bt5YxPp+ct362pqGf70Qn0vmKN131jZE4e0w3KTyz2X6fGSGFBeMYUu4FBLgu5JRTBzy4O9aohcQ==" /></div>      <input class="form-control" id="repository_id" name="repository_id" type="hidden" value="51852679" />

        <div class="select-menu js-menu-container js-select-menu">
          <a href="/AuraUAS/navigation/subscription"
            class="btn btn-sm btn-with-count select-menu-button js-menu-target"
            role="button"
            aria-haspopup="true"
            aria-expanded="false"
            aria-label="Toggle repository notifications menu"
            data-ga-click="Repository, click Watch settings, action:blob#show">
            <span class="js-select-button">
                <svg aria-hidden="true" class="octicon octicon-eye" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M8.06 2C3 2 0 8 0 8s3 6 8.06 6C13 14 16 8 16 8s-3-6-7.94-6zM8 12c-2.2 0-4-1.78-4-4 0-2.2 1.8-4 4-4 2.22 0 4 1.8 4 4 0 2.22-1.78 4-4 4zm2-4c0 1.11-.89 2-2 2-1.11 0-2-.89-2-2 0-1.11.89-2 2-2 1.11 0 2 .89 2 2z"/></svg>
                Unwatch
            </span>
          </a>
            <a class="social-count js-social-count"
              href="/AuraUAS/navigation/watchers"
              aria-label="7 users are watching this repository">
              7
            </a>

        <div class="select-menu-modal-holder">
          <div class="select-menu-modal subscription-menu-modal js-menu-content">
            <div class="select-menu-header js-navigation-enable" tabindex="-1">
              <svg aria-label="Close" class="octicon octicon-x js-menu-close" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M7.48 8l3.75 3.75-1.48 1.48L6 9.48l-3.75 3.75-1.48-1.48L4.52 8 .77 4.25l1.48-1.48L6 6.52l3.75-3.75 1.48 1.48z"/></svg>
              <span class="select-menu-title">Notifications</span>
            </div>

              <div class="select-menu-list js-navigation-container" role="menu">

                <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
                  <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
                  <div class="select-menu-item-text">
                    <input id="do_included" name="do" type="radio" value="included" />
                    <span class="select-menu-item-heading">Not watching</span>
                    <span class="description">Be notified when participating or @mentioned.</span>
                    <span class="js-select-button-text hidden-select-button-text">
                      <svg aria-hidden="true" class="octicon octicon-eye" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M8.06 2C3 2 0 8 0 8s3 6 8.06 6C13 14 16 8 16 8s-3-6-7.94-6zM8 12c-2.2 0-4-1.78-4-4 0-2.2 1.8-4 4-4 2.22 0 4 1.8 4 4 0 2.22-1.78 4-4 4zm2-4c0 1.11-.89 2-2 2-1.11 0-2-.89-2-2 0-1.11.89-2 2-2 1.11 0 2 .89 2 2z"/></svg>
                      Watch
                    </span>
                  </div>
                </div>

                <div class="select-menu-item js-navigation-item selected" role="menuitem" tabindex="0">
                  <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
                  <div class="select-menu-item-text">
                    <input checked="checked" id="do_subscribed" name="do" type="radio" value="subscribed" />
                    <span class="select-menu-item-heading">Watching</span>
                    <span class="description">Be notified of all conversations.</span>
                    <span class="js-select-button-text hidden-select-button-text">
                      <svg aria-hidden="true" class="octicon octicon-eye" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M8.06 2C3 2 0 8 0 8s3 6 8.06 6C13 14 16 8 16 8s-3-6-7.94-6zM8 12c-2.2 0-4-1.78-4-4 0-2.2 1.8-4 4-4 2.22 0 4 1.8 4 4 0 2.22-1.78 4-4 4zm2-4c0 1.11-.89 2-2 2-1.11 0-2-.89-2-2 0-1.11.89-2 2-2 1.11 0 2 .89 2 2z"/></svg>
                        Unwatch
                    </span>
                  </div>
                </div>

                <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
                  <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
                  <div class="select-menu-item-text">
                    <input id="do_ignore" name="do" type="radio" value="ignore" />
                    <span class="select-menu-item-heading">Ignoring</span>
                    <span class="description">Never be notified.</span>
                    <span class="js-select-button-text hidden-select-button-text">
                      <svg aria-hidden="true" class="octicon octicon-mute" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M8 2.81v10.38c0 .67-.81 1-1.28.53L3 10H1c-.55 0-1-.45-1-1V7c0-.55.45-1 1-1h2l3.72-3.72C7.19 1.81 8 2.14 8 2.81zm7.53 3.22l-1.06-1.06-1.97 1.97-1.97-1.97-1.06 1.06L11.44 8 9.47 9.97l1.06 1.06 1.97-1.97 1.97 1.97 1.06-1.06L13.56 8l1.97-1.97z"/></svg>
                        Stop ignoring
                    </span>
                  </div>
                </div>

              </div>

            </div>
          </div>
        </div>
</form>
  </li>

  <li>
    
  <div class="js-toggler-container js-social-container starring-container ">
    <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/AuraUAS/navigation/unstar" class="starred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="rVWUY5EttIO7mNhoiVYL7zmqDh6yrMwWHkOZqc9XX3m/Gbp+PA3c0+6Y/yJefZetqW4Rse6nP+8KhkEsUM0LqA==" /></div>
      <button
        type="submit"
        class="btn btn-sm btn-with-count js-toggler-target"
        aria-label="Unstar this repository" title="Unstar AuraUAS/navigation"
        data-ga-click="Repository, click unstar button, action:blob#show; text:Unstar">
        <svg aria-hidden="true" class="octicon octicon-star" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M14 6l-4.9-.64L7 1 4.9 5.36 0 6l3.6 3.26L2.67 14 7 11.67 11.33 14l-.93-4.74z"/></svg>
        Unstar
      </button>
        <a class="social-count js-social-count" href="/AuraUAS/navigation/stargazers"
           aria-label="12 users starred this repository">
          12
        </a>
</form>
    <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/AuraUAS/navigation/star" class="unstarred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="3sF7kKJ/knRRm40NosVIUnPbwtUJaQ2WWfeYiiR/UR54Iv1QPqdvNYEiNCJSQ2ig/ON9qNh94TLquieLBfJv4Q==" /></div>
      <button
        type="submit"
        class="btn btn-sm btn-with-count js-toggler-target"
        aria-label="Star this repository" title="Star AuraUAS/navigation"
        data-ga-click="Repository, click star button, action:blob#show; text:Star">
        <svg aria-hidden="true" class="octicon octicon-star" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M14 6l-4.9-.64L7 1 4.9 5.36 0 6l3.6 3.26L2.67 14 7 11.67 11.33 14l-.93-4.74z"/></svg>
        Star
      </button>
        <a class="social-count js-social-count" href="/AuraUAS/navigation/stargazers"
           aria-label="12 users starred this repository">
          12
        </a>
</form>  </div>

  </li>

  <li>
          <a href="#fork-destination-box" class="btn btn-sm btn-with-count"
              title="Fork your own copy of AuraUAS/navigation to your account"
              aria-label="Fork your own copy of AuraUAS/navigation to your account"
              rel="facebox"
              data-ga-click="Repository, show fork modal, action:blob#show; text:Fork">
              <svg aria-hidden="true" class="octicon octicon-repo-forked" height="16" version="1.1" viewBox="0 0 10 16" width="10"><path fill-rule="evenodd" d="M8 1a1.993 1.993 0 0 0-1 3.72V6L5 8 3 6V4.72A1.993 1.993 0 0 0 2 1a1.993 1.993 0 0 0-1 3.72V6.5l3 3v1.78A1.993 1.993 0 0 0 5 15a1.993 1.993 0 0 0 1-3.72V9.5l3-3V4.72A1.993 1.993 0 0 0 8 1zM2 4.2C1.34 4.2.8 3.65.8 3c0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2zm3 10c-.66 0-1.2-.55-1.2-1.2 0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2zm3-10c-.66 0-1.2-.55-1.2-1.2 0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2z"/></svg>
            Fork
          </a>

          <div id="fork-destination-box" style="display: none;">
            <h2 class="facebox-header" data-facebox-id="facebox-header">Where should we fork this repository?</h2>
            <include-fragment src=""
                class="js-fork-select-fragment fork-select-fragment"
                data-url="/AuraUAS/navigation/fork?fragment=1">
              <img alt="Loading" height="64" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-128.gif" width="64" />
            </include-fragment>
          </div>

    <a href="/AuraUAS/navigation/network" class="social-count"
       aria-label="2 users forked this repository">
      2
    </a>
  </li>
</ul>

        <h1 class="public ">
  <svg aria-hidden="true" class="octicon octicon-repo" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M4 9H3V8h1v1zm0-3H3v1h1V6zm0-2H3v1h1V4zm0-2H3v1h1V2zm8-1v12c0 .55-.45 1-1 1H6v2l-1.5-1.5L3 16v-2H1c-.55 0-1-.45-1-1V1c0-.55.45-1 1-1h10c.55 0 1 .45 1 1zm-1 10H1v2h2v-1h3v1h5v-2zm0-10H2v9h9V1z"/></svg>
  <span class="author" itemprop="author"><a href="/AuraUAS" class="url fn" rel="author">AuraUAS</a></span><!--
--><span class="path-divider">/</span><!--
--><strong itemprop="name"><a href="/AuraUAS/navigation" data-pjax="#js-repo-pjax-container">navigation</a></strong>

</h1>

      </div>
      <div class="container">
        
<nav class="reponav js-repo-nav js-sidenav-container-pjax"
     itemscope
     itemtype="http://schema.org/BreadcrumbList"
     role="navigation"
     data-pjax="#js-repo-pjax-container">

  <span itemscope itemtype="http://schema.org/ListItem" itemprop="itemListElement">
    <a href="/AuraUAS/navigation" class="js-selected-navigation-item selected reponav-item" data-hotkey="g c" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /AuraUAS/navigation" itemprop="url">
      <svg aria-hidden="true" class="octicon octicon-code" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M9.5 3L8 4.5 11.5 8 8 11.5 9.5 13 14 8 9.5 3zm-5 0L0 8l4.5 5L6 11.5 2.5 8 6 4.5 4.5 3z"/></svg>
      <span itemprop="name">Code</span>
      <meta itemprop="position" content="1">
</a>  </span>

    <span itemscope itemtype="http://schema.org/ListItem" itemprop="itemListElement">
      <a href="/AuraUAS/navigation/issues" class="js-selected-navigation-item reponav-item" data-hotkey="g i" data-selected-links="repo_issues repo_labels repo_milestones /AuraUAS/navigation/issues" itemprop="url">
        <svg aria-hidden="true" class="octicon octicon-issue-opened" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 0 1 1.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"/></svg>
        <span itemprop="name">Issues</span>
        <span class="Counter">0</span>
        <meta itemprop="position" content="2">
</a>    </span>

  <span itemscope itemtype="http://schema.org/ListItem" itemprop="itemListElement">
    <a href="/AuraUAS/navigation/pulls" class="js-selected-navigation-item reponav-item" data-hotkey="g p" data-selected-links="repo_pulls /AuraUAS/navigation/pulls" itemprop="url">
      <svg aria-hidden="true" class="octicon octicon-git-pull-request" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M11 11.28V5c-.03-.78-.34-1.47-.94-2.06C9.46 2.35 8.78 2.03 8 2H7V0L4 3l3 3V4h1c.27.02.48.11.69.31.21.2.3.42.31.69v6.28A1.993 1.993 0 0 0 10 15a1.993 1.993 0 0 0 1-3.72zm-1 2.92c-.66 0-1.2-.55-1.2-1.2 0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2zM4 3c0-1.11-.89-2-2-2a1.993 1.993 0 0 0-1 3.72v6.56A1.993 1.993 0 0 0 2 15a1.993 1.993 0 0 0 1-3.72V4.72c.59-.34 1-.98 1-1.72zm-.8 10c0 .66-.55 1.2-1.2 1.2-.65 0-1.2-.55-1.2-1.2 0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2zM2 4.2C1.34 4.2.8 3.65.8 3c0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2z"/></svg>
      <span itemprop="name">Pull requests</span>
      <span class="Counter">0</span>
      <meta itemprop="position" content="3">
</a>  </span>

    <a href="/AuraUAS/navigation/projects" class="js-selected-navigation-item reponav-item" data-selected-links="repo_projects new_repo_project repo_project /AuraUAS/navigation/projects">
      <svg aria-hidden="true" class="octicon octicon-project" height="16" version="1.1" viewBox="0 0 15 16" width="15"><path fill-rule="evenodd" d="M10 12h3V2h-3v10zm-4-2h3V2H6v8zm-4 4h3V2H2v12zm-1 1h13V1H1v14zM14 0H1a1 1 0 0 0-1 1v14a1 1 0 0 0 1 1h13a1 1 0 0 0 1-1V1a1 1 0 0 0-1-1z"/></svg>
      Projects
      <span class="Counter" >0</span>
</a>
    <a href="/AuraUAS/navigation/wiki" class="js-selected-navigation-item reponav-item" data-hotkey="g w" data-selected-links="repo_wiki /AuraUAS/navigation/wiki">
      <svg aria-hidden="true" class="octicon octicon-book" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M3 5h4v1H3V5zm0 3h4V7H3v1zm0 2h4V9H3v1zm11-5h-4v1h4V5zm0 2h-4v1h4V7zm0 2h-4v1h4V9zm2-6v9c0 .55-.45 1-1 1H9.5l-1 1-1-1H2c-.55 0-1-.45-1-1V3c0-.55.45-1 1-1h5.5l1 1 1-1H15c.55 0 1 .45 1 1zm-8 .5L7.5 3H2v9h6V3.5zm7-.5H9.5l-.5.5V12h6V3z"/></svg>
      Wiki
</a>

    <div class="reponav-dropdown js-menu-container">
      <button type="button" class="btn-link reponav-item reponav-dropdown js-menu-target " data-no-toggle aria-expanded="false" aria-haspopup="true">
        Insights
        <svg aria-hidden="true" class="octicon octicon-triangle-down v-align-middle text-gray" height="11" version="1.1" viewBox="0 0 12 16" width="8"><path fill-rule="evenodd" d="M0 5l6 6 6-6z"/></svg>
      </button>
      <div class="dropdown-menu-content js-menu-content">
        <div class="dropdown-menu dropdown-menu-sw">
          <a class="dropdown-item" href="/AuraUAS/navigation/pulse" data-skip-pjax>
            <svg aria-hidden="true" class="octicon octicon-pulse" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M11.5 8L8.8 5.4 6.6 8.5 5.5 1.6 2.38 8H0v2h3.6l.9-1.8.9 5.4L9 8.5l1.6 1.5H14V8z"/></svg>
            Pulse
          </a>
          <a class="dropdown-item" href="/AuraUAS/navigation/graphs" data-skip-pjax>
            <svg aria-hidden="true" class="octicon octicon-graph" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M16 14v1H0V0h1v14h15zM5 13H3V8h2v5zm4 0H7V3h2v10zm4 0h-2V6h2v7z"/></svg>
            Graphs
          </a>
        </div>
      </div>
    </div>
</nav>

      </div>
    </div>

<div class="container new-discussion-timeline experiment-repo-nav">
  <div class="repository-content">

    
  <a href="/AuraUAS/navigation/blob/a2e40348adf1541f959271db0904e67ebdb392fe/src/nav_eigen/EKF_15state.cxx" class="d-none js-permalink-shortcut" data-hotkey="y">Permalink</a>

  <!-- blob contrib key: blob_contributors:v21:809e593f5b0ea3b6ac7ec5b3b2c3b68d -->

  <div class="file-navigation js-zeroclipboard-container">
    
<div class="select-menu branch-select-menu js-menu-container js-select-menu float-left">
  <button class=" btn btn-sm select-menu-button js-menu-target css-truncate" data-hotkey="w"
    
    type="button" aria-label="Switch branches or tags" aria-expanded="false" aria-haspopup="true">
      <i>Branch:</i>
      <span class="js-select-button css-truncate-target">master</span>
  </button>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax>

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <svg aria-label="Close" class="octicon octicon-x js-menu-close" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M7.48 8l3.75 3.75-1.48 1.48L6 9.48l-3.75 3.75-1.48-1.48L4.52 8 .77 4.25l1.48-1.48L6 6.52l3.75-3.75 1.48 1.48z"/></svg>
        <span class="select-menu-title">Switch branches/tags</span>
      </div>

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="form-control js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" data-filter-placeholder="Filter branches/tags" class="js-select-menu-tab" role="tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" data-filter-placeholder="Find a tag…" class="js-select-menu-tab" role="tab">Tags</a>
            </li>
          </ul>
        </div>
      </div>

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches" role="menu">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/AuraUAS/navigation/blob/csv/src/nav_eigen/EKF_15state.cxx"
               data-name="csv"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text">
                csv
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/AuraUAS/navigation/blob/libtool/src/nav_eigen/EKF_15state.cxx"
               data-name="libtool"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text">
                libtool
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open selected"
               href="/AuraUAS/navigation/blob/master/src/nav_eigen/EKF_15state.cxx"
               data-name="master"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text">
                master
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/AuraUAS/navigation/blob/work1/src/nav_eigen/EKF_15state.cxx"
               data-name="work1"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M12 5l-8 8-4-4 1.5-1.5L4 10l6.5-6.5z"/></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text">
                work1
              </span>
            </a>
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div>

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div>

    </div>
  </div>
</div>

    <div class="BtnGroup float-right">
      <a href="/AuraUAS/navigation/find/master"
            class="js-pjax-capture-input btn btn-sm BtnGroup-item"
            data-pjax
            data-hotkey="t">
        Find file
      </a>
      <button aria-label="Copy file path to clipboard" class="js-zeroclipboard btn btn-sm BtnGroup-item tooltipped tooltipped-s" data-copied-hint="Copied!" type="button">Copy path</button>
    </div>
    <div class="breadcrumb js-zeroclipboard-target">
      <span class="repo-root js-repo-root"><span class="js-path-segment"><a href="/AuraUAS/navigation"><span>navigation</span></a></span></span><span class="separator">/</span><span class="js-path-segment"><a href="/AuraUAS/navigation/tree/master/src"><span>src</span></a></span><span class="separator">/</span><span class="js-path-segment"><a href="/AuraUAS/navigation/tree/master/src/nav_eigen"><span>nav_eigen</span></a></span><span class="separator">/</span><strong class="final-path">EKF_15state.cxx</strong>
    </div>
  </div>


  
  <div class="commit-tease">
      <span class="float-right">
        <a class="commit-tease-sha" href="/AuraUAS/navigation/commit/079fd083ff1ecf290ed6063c2afb291520cb410d" data-pjax>
          079fd08
        </a>
        <relative-time datetime="2017-03-13T14:30:16Z">Mar 13, 2017</relative-time>
      </span>
      <div>
        <img alt="" class="avatar" data-canonical-src="https://0.gravatar.com/avatar/86b7d1aa3cada428b804e26296a92a82?d=https%3A%2F%2Fassets-cdn.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png&amp;r=x&amp;s=140" height="20" src="https://camo.githubusercontent.com/d5ef81b1bf1e19e281a159dad3ff0845879eb923/68747470733a2f2f302e67726176617461722e636f6d2f6176617461722f38366237643161613363616461343238623830346532363239366139326138323f643d68747470732533412532462532466173736574732d63646e2e6769746875622e636f6d253246696d6167657325324667726176617461727325324667726176617461722d757365722d3432302e706e6726723d7826733d313430" width="20" />
        <span class="user-mention">Curtis L. Olson</span>
          <a href="/AuraUAS/navigation/commit/079fd083ff1ecf290ed6063c2afb291520cb410d" class="message" data-pjax="true" title="Wrap boost python code in a macro to facilitate compiling for straight up
C applications.">Wrap boost python code in a macro to facilitate compiling for straigh…</a>
      </div>

    <div class="commit-tease-contributors">
      <button type="button" class="btn-link muted-link contributors-toggle" data-facebox="#blob_contributors_box">
        <strong>1</strong>
         contributor
      </button>
      
    </div>

    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header" data-facebox-id="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list" data-facebox-id="facebox-description">
          <li class="facebox-user-list-item">
            <img alt="@clolsonus" height="24" src="https://avatars6.githubusercontent.com/u/11504653?v=4&amp;s=48" width="24" />
            <a href="/clolsonus">clolsonus</a>
          </li>
      </ul>
    </div>
  </div>

  <div class="file">
    <div class="file-header">
  <div class="file-actions">

    <div class="BtnGroup">
      <a href="/AuraUAS/navigation/raw/master/src/nav_eigen/EKF_15state.cxx" class="btn btn-sm BtnGroup-item" id="raw-url">Raw</a>
        <a href="/AuraUAS/navigation/blame/master/src/nav_eigen/EKF_15state.cxx" class="btn btn-sm js-update-url-with-hash BtnGroup-item" data-hotkey="b">Blame</a>
      <a href="/AuraUAS/navigation/commits/master/src/nav_eigen/EKF_15state.cxx" class="btn btn-sm BtnGroup-item" rel="nofollow">History</a>
    </div>

        <a class="btn-octicon tooltipped tooltipped-nw"
           href="github-windows://openRepo/https://github.com/AuraUAS/navigation?branch=master&amp;filepath=src%2Fnav_eigen%2FEKF_15state.cxx"
           aria-label="Open this file in GitHub Desktop"
           data-ga-click="Repository, open with desktop, type:windows">
            <svg aria-hidden="true" class="octicon octicon-device-desktop" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M15 2H1c-.55 0-1 .45-1 1v9c0 .55.45 1 1 1h5.34c-.25.61-.86 1.39-2.34 2h8c-1.48-.61-2.09-1.39-2.34-2H15c.55 0 1-.45 1-1V3c0-.55-.45-1-1-1zm0 9H1V3h14v8z"/></svg>
        </a>

        <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/AuraUAS/navigation/edit/master/src/nav_eigen/EKF_15state.cxx" class="inline-form js-update-url-with-hash" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="3jEDRaETwYQwGSWlZ8nPROjx5mevORyp33nJR4DS9pE5pVsYYZMFey0w0YFUkTYslYUbOPJAknwO26HE08I1Tg==" /></div>
          <button class="btn-octicon tooltipped tooltipped-nw" type="submit"
            aria-label="Fork this project and edit the file" data-hotkey="e" data-disable-with>
            <svg aria-hidden="true" class="octicon octicon-pencil" height="16" version="1.1" viewBox="0 0 14 16" width="14"><path fill-rule="evenodd" d="M0 12v3h3l8-8-3-3-8 8zm3 2H1v-2h1v1h1v1zm10.3-9.3L12 6 9 3l1.3-1.3a.996.996 0 0 1 1.41 0l1.59 1.59c.39.39.39 1.02 0 1.41z"/></svg>
          </button>
</form>        <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="/AuraUAS/navigation/delete/master/src/nav_eigen/EKF_15state.cxx" class="inline-form" method="post"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /><input name="authenticity_token" type="hidden" value="XRbh3acuE1JZ8zRFGdoNPvztMV8hvFhlFVqo7hJnJKjw5+sjbv4GJmK6rNUCJH4T5lcntAzLhP1r77ponPtFjg==" /></div>
          <button class="btn-octicon btn-octicon-danger tooltipped tooltipped-nw" type="submit"
            aria-label="Fork this project and delete the file" data-disable-with>
            <svg aria-hidden="true" class="octicon octicon-trashcan" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M11 2H9c0-.55-.45-1-1-1H5c-.55 0-1 .45-1 1H2c-.55 0-1 .45-1 1v1c0 .55.45 1 1 1v9c0 .55.45 1 1 1h7c.55 0 1-.45 1-1V5c.55 0 1-.45 1-1V3c0-.55-.45-1-1-1zm-1 12H3V5h1v8h1V5h1v8h1V5h1v8h1V5h1v9zm1-10H2V3h9v1z"/></svg>
          </button>
</form>  </div>

  <div class="file-info">
      404 lines (318 sloc)
      <span class="file-info-divider"></span>
    12.8 KB
  </div>
</div>

    

  <div itemprop="text" class="blob-wrapper data type-c">
      <table class="highlight tab-size js-file-line-container" data-tab-size="8">
      <tr>
        <td id="L1" class="blob-num js-line-number" data-line-number="1"></td>
        <td id="LC1" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">/*</span>! \file EKF_15state.c</span></td>
      </tr>
      <tr>
        <td id="L2" class="blob-num js-line-number" data-line-number="2"></td>
        <td id="LC2" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *	\brief 15 state EKF navigation filter</span></td>
      </tr>
      <tr>
        <td id="L3" class="blob-num js-line-number" data-line-number="3"></td>
        <td id="LC3" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *</span></td>
      </tr>
      <tr>
        <td id="L4" class="blob-num js-line-number" data-line-number="4"></td>
        <td id="LC4" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *	\details  15 state EKF navigation filter using loosely integrated INS/GPS architecture.</span></td>
      </tr>
      <tr>
        <td id="L5" class="blob-num js-line-number" data-line-number="5"></td>
        <td id="LC5" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> * 	Time update is done after every IMU data acquisition and GPS measurement</span></td>
      </tr>
      <tr>
        <td id="L6" class="blob-num js-line-number" data-line-number="6"></td>
        <td id="LC6" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> * 	update is done every time the new data flag in the GPS data packet is set. Designed by Adhika Lie.</span></td>
      </tr>
      <tr>
        <td id="L7" class="blob-num js-line-number" data-line-number="7"></td>
        <td id="LC7" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *	Attitude is parameterized using quaternions.</span></td>
      </tr>
      <tr>
        <td id="L8" class="blob-num js-line-number" data-line-number="8"></td>
        <td id="LC8" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *	Estimates IMU bias errors.</span></td>
      </tr>
      <tr>
        <td id="L9" class="blob-num js-line-number" data-line-number="9"></td>
        <td id="LC9" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *	\ingroup nav_fcns</span></td>
      </tr>
      <tr>
        <td id="L10" class="blob-num js-line-number" data-line-number="10"></td>
        <td id="LC10" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *</span></td>
      </tr>
      <tr>
        <td id="L11" class="blob-num js-line-number" data-line-number="11"></td>
        <td id="LC11" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> * \author University of Minnesota</span></td>
      </tr>
      <tr>
        <td id="L12" class="blob-num js-line-number" data-line-number="12"></td>
        <td id="LC12" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> * \author Aerospace Engineering and Mechanics</span></td>
      </tr>
      <tr>
        <td id="L13" class="blob-num js-line-number" data-line-number="13"></td>
        <td id="LC13" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.</span></td>
      </tr>
      <tr>
        <td id="L14" class="blob-num js-line-number" data-line-number="14"></td>
        <td id="LC14" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> *</span></td>
      </tr>
      <tr>
        <td id="L15" class="blob-num js-line-number" data-line-number="15"></td>
        <td id="LC15" class="blob-code blob-code-inner js-file-line"><span class="pl-c"> <span class="pl-c">*/</span></span></td>
      </tr>
      <tr>
        <td id="L16" class="blob-num js-line-number" data-line-number="16"></td>
        <td id="LC16" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L17" class="blob-num js-line-number" data-line-number="17"></td>
        <td id="LC17" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>iostream<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L18" class="blob-num js-line-number" data-line-number="18"></td>
        <td id="LC18" class="blob-code blob-code-inner js-file-line"><span class="pl-k">using</span> std::cout;</td>
      </tr>
      <tr>
        <td id="L19" class="blob-num js-line-number" data-line-number="19"></td>
        <td id="LC19" class="blob-code blob-code-inner js-file-line"><span class="pl-k">using</span> std::endl;</td>
      </tr>
      <tr>
        <td id="L20" class="blob-num js-line-number" data-line-number="20"></td>
        <td id="LC20" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>stdio.h<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L21" class="blob-num js-line-number" data-line-number="21"></td>
        <td id="LC21" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L22" class="blob-num js-line-number" data-line-number="22"></td>
        <td id="LC22" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>../core/nav_functions.hxx<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L23" class="blob-num js-line-number" data-line-number="23"></td>
        <td id="LC23" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>EKF_15state.hxx<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L24" class="blob-num js-line-number" data-line-number="24"></td>
        <td id="LC24" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L25" class="blob-num js-line-number" data-line-number="25"></td>
        <td id="LC25" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> P_P_INIT = <span class="pl-c1">10.0</span>;</td>
      </tr>
      <tr>
        <td id="L26" class="blob-num js-line-number" data-line-number="26"></td>
        <td id="LC26" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> P_V_INIT = <span class="pl-c1">1.0</span>;</td>
      </tr>
      <tr>
        <td id="L27" class="blob-num js-line-number" data-line-number="27"></td>
        <td id="LC27" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> P_A_INIT = <span class="pl-c1">0.34906</span>;   <span class="pl-c"><span class="pl-c">//</span> 20 deg</span></td>
      </tr>
      <tr>
        <td id="L28" class="blob-num js-line-number" data-line-number="28"></td>
        <td id="LC28" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> P_HDG_INIT = <span class="pl-c1">3.14159</span>; <span class="pl-c"><span class="pl-c">//</span> 180 deg</span></td>
      </tr>
      <tr>
        <td id="L29" class="blob-num js-line-number" data-line-number="29"></td>
        <td id="LC29" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> P_AB_INIT = <span class="pl-c1">0.9810</span>;   <span class="pl-c"><span class="pl-c">//</span> 0.5*g</span></td>
      </tr>
      <tr>
        <td id="L30" class="blob-num js-line-number" data-line-number="30"></td>
        <td id="LC30" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> P_GB_INIT = <span class="pl-c1">0.01745</span>;  <span class="pl-c"><span class="pl-c">//</span> 5 deg/s</span></td>
      </tr>
      <tr>
        <td id="L31" class="blob-num js-line-number" data-line-number="31"></td>
        <td id="LC31" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L32" class="blob-num js-line-number" data-line-number="32"></td>
        <td id="LC32" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> Rew = <span class="pl-c1">6.359058719353925e+006</span>; <span class="pl-c"><span class="pl-c">//</span> earth radius</span></td>
      </tr>
      <tr>
        <td id="L33" class="blob-num js-line-number" data-line-number="33"></td>
        <td id="LC33" class="blob-code blob-code-inner js-file-line"><span class="pl-k">const</span> <span class="pl-k">double</span> Rns = <span class="pl-c1">6.386034030458164e+006</span>; <span class="pl-c"><span class="pl-c">//</span> earth radius</span></td>
      </tr>
      <tr>
        <td id="L34" class="blob-num js-line-number" data-line-number="34"></td>
        <td id="LC34" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L35" class="blob-num js-line-number" data-line-number="35"></td>
        <td id="LC35" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> BRT: (1) I think there are some several identity and sparse</span></td>
      </tr>
      <tr>
        <td id="L36" class="blob-num js-line-number" data-line-number="36"></td>
        <td id="LC36" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> matrices, so probably some optimization still left there.  (2)</span></td>
      </tr>
      <tr>
        <td id="L37" class="blob-num js-line-number" data-line-number="37"></td>
        <td id="LC37" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> Seems like a lot of the transforms could be more efficiently done</span></td>
      </tr>
      <tr>
        <td id="L38" class="blob-num js-line-number" data-line-number="38"></td>
        <td id="LC38" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> with just a matrix or vector multiply.  (3) Probably could do a lot</span></td>
      </tr>
      <tr>
        <td id="L39" class="blob-num js-line-number" data-line-number="39"></td>
        <td id="LC39" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> of block operations with F, i.e. F.block(j,k) = C_B2N, etc.  (4) A</span></td>
      </tr>
      <tr>
        <td id="L40" class="blob-num js-line-number" data-line-number="40"></td>
        <td id="LC40" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> lot of these multi line equations with temp matrices can be</span></td>
      </tr>
      <tr>
        <td id="L41" class="blob-num js-line-number" data-line-number="41"></td>
        <td id="LC41" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> compressed.</span></td>
      </tr>
      <tr>
        <td id="L42" class="blob-num js-line-number" data-line-number="42"></td>
        <td id="LC42" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L43" class="blob-num js-line-number" data-line-number="43"></td>
        <td id="LC43" class="blob-code blob-code-inner js-file-line"><span class="pl-k">void</span> <span class="pl-en">EKF15::set_config</span>(NAVconfig config) {</td>
      </tr>
      <tr>
        <td id="L44" class="blob-num js-line-number" data-line-number="44"></td>
        <td id="LC44" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">this</span>-&gt;config = config;</td>
      </tr>
      <tr>
        <td id="L45" class="blob-num js-line-number" data-line-number="45"></td>
        <td id="LC45" class="blob-code blob-code-inner js-file-line">}</td>
      </tr>
      <tr>
        <td id="L46" class="blob-num js-line-number" data-line-number="46"></td>
        <td id="LC46" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L47" class="blob-num js-line-number" data-line-number="47"></td>
        <td id="LC47" class="blob-code blob-code-inner js-file-line">NAVconfig <span class="pl-en">EKF15::get_config</span>() {</td>
      </tr>
      <tr>
        <td id="L48" class="blob-num js-line-number" data-line-number="48"></td>
        <td id="LC48" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">return</span> config;</td>
      </tr>
      <tr>
        <td id="L49" class="blob-num js-line-number" data-line-number="49"></td>
        <td id="LC49" class="blob-code blob-code-inner js-file-line">}</td>
      </tr>
      <tr>
        <td id="L50" class="blob-num js-line-number" data-line-number="50"></td>
        <td id="LC50" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L51" class="blob-num js-line-number" data-line-number="51"></td>
        <td id="LC51" class="blob-code blob-code-inner js-file-line"><span class="pl-k">void</span> <span class="pl-en">EKF15::default_config</span>()</td>
      </tr>
      <tr>
        <td id="L52" class="blob-num js-line-number" data-line-number="52"></td>
        <td id="LC52" class="blob-code blob-code-inner js-file-line">{</td>
      </tr>
      <tr>
        <td id="L53" class="blob-num js-line-number" data-line-number="53"></td>
        <td id="LC53" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_w_ax</span> = <span class="pl-c1">0.05</span>;     <span class="pl-c"><span class="pl-c">//</span> Std dev of Accelerometer Wide Band Noise (m/s^2)</span></td>
      </tr>
      <tr>
        <td id="L54" class="blob-num js-line-number" data-line-number="54"></td>
        <td id="LC54" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_w_ay</span> = <span class="pl-c1">0.05</span>;</td>
      </tr>
      <tr>
        <td id="L55" class="blob-num js-line-number" data-line-number="55"></td>
        <td id="LC55" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_w_az</span> = <span class="pl-c1">0.05</span>;</td>
      </tr>
      <tr>
        <td id="L56" class="blob-num js-line-number" data-line-number="56"></td>
        <td id="LC56" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_w_gx</span> = <span class="pl-c1">0.00175</span>;  <span class="pl-c"><span class="pl-c">//</span> Std dev of gyro output noise (rad/s)  (0.1 deg/s)</span></td>
      </tr>
      <tr>
        <td id="L57" class="blob-num js-line-number" data-line-number="57"></td>
        <td id="LC57" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_w_gy</span> = <span class="pl-c1">0.00175</span>;</td>
      </tr>
      <tr>
        <td id="L58" class="blob-num js-line-number" data-line-number="58"></td>
        <td id="LC58" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_w_gz</span> = <span class="pl-c1">0.00175</span>;</td>
      </tr>
      <tr>
        <td id="L59" class="blob-num js-line-number" data-line-number="59"></td>
        <td id="LC59" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_a_d</span>  = <span class="pl-c1">0.01</span>;     <span class="pl-c"><span class="pl-c">//</span> Std dev of Accelerometer Markov Bias</span></td>
      </tr>
      <tr>
        <td id="L60" class="blob-num js-line-number" data-line-number="60"></td>
        <td id="LC60" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">tau_a</span>    = <span class="pl-c1">100.0</span>;    <span class="pl-c"><span class="pl-c">//</span> Correlation time or time constant of b_{ad}</span></td>
      </tr>
      <tr>
        <td id="L61" class="blob-num js-line-number" data-line-number="61"></td>
        <td id="LC61" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_g_d</span>  = <span class="pl-c1">0.00025</span>;  <span class="pl-c"><span class="pl-c">//</span> Std dev of correlated gyro bias (rad)</span></td>
      </tr>
      <tr>
        <td id="L62" class="blob-num js-line-number" data-line-number="62"></td>
        <td id="LC62" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">tau_g</span>    = <span class="pl-c1">50.0</span>;     <span class="pl-c"><span class="pl-c">//</span> Correlation time or time constant of b_{gd}</span></td>
      </tr>
      <tr>
        <td id="L63" class="blob-num js-line-number" data-line-number="63"></td>
        <td id="LC63" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_gps_p_ne</span> = <span class="pl-c1">3.0</span>;  <span class="pl-c"><span class="pl-c">//</span> GPS measurement noise std dev (m)</span></td>
      </tr>
      <tr>
        <td id="L64" class="blob-num js-line-number" data-line-number="64"></td>
        <td id="LC64" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_gps_p_d</span>  = <span class="pl-c1">6.0</span>;  <span class="pl-c"><span class="pl-c">//</span> GPS measurement noise std dev (m)</span></td>
      </tr>
      <tr>
        <td id="L65" class="blob-num js-line-number" data-line-number="65"></td>
        <td id="LC65" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_gps_v_ne</span> = <span class="pl-c1">0.5</span>;  <span class="pl-c"><span class="pl-c">//</span> GPS measurement noise std dev (m/s)</span></td>
      </tr>
      <tr>
        <td id="L66" class="blob-num js-line-number" data-line-number="66"></td>
        <td id="LC66" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_gps_v_d</span>  = <span class="pl-c1">1.0</span>;  <span class="pl-c"><span class="pl-c">//</span> GPS measurement noise std dev (m/s)</span></td>
      </tr>
      <tr>
        <td id="L67" class="blob-num js-line-number" data-line-number="67"></td>
        <td id="LC67" class="blob-code blob-code-inner js-file-line">    config.<span class="pl-smi">sig_mag</span>      = <span class="pl-c1">0.3</span>;  <span class="pl-c"><span class="pl-c">//</span> Magnetometer measurement noise std dev (normalized -1 to 1)</span></td>
      </tr>
      <tr>
        <td id="L68" class="blob-num js-line-number" data-line-number="68"></td>
        <td id="LC68" class="blob-code blob-code-inner js-file-line">}</td>
      </tr>
      <tr>
        <td id="L69" class="blob-num js-line-number" data-line-number="69"></td>
        <td id="LC69" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L70" class="blob-num js-line-number" data-line-number="70"></td>
        <td id="LC70" class="blob-code blob-code-inner js-file-line">NAVdata <span class="pl-en">EKF15::init</span>(IMUdata imu, GPSdata gps) {</td>
      </tr>
      <tr>
        <td id="L71" class="blob-num js-line-number" data-line-number="71"></td>
        <td id="LC71" class="blob-code blob-code-inner js-file-line">    I15.<span class="pl-c1">setIdentity</span>();</td>
      </tr>
      <tr>
        <td id="L72" class="blob-num js-line-number" data-line-number="72"></td>
        <td id="LC72" class="blob-code blob-code-inner js-file-line">    I3.<span class="pl-c1">setIdentity</span>();</td>
      </tr>
      <tr>
        <td id="L73" class="blob-num js-line-number" data-line-number="73"></td>
        <td id="LC73" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L74" class="blob-num js-line-number" data-line-number="74"></td>
        <td id="LC74" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Assemble the matrices</span></td>
      </tr>
      <tr>
        <td id="L75" class="blob-num js-line-number" data-line-number="75"></td>
        <td id="LC75" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> .... gravity, g</span></td>
      </tr>
      <tr>
        <td id="L76" class="blob-num js-line-number" data-line-number="76"></td>
        <td id="LC76" class="blob-code blob-code-inner js-file-line">    grav = <span class="pl-c1">Vector3d</span>(<span class="pl-c1">0.0</span>, <span class="pl-c1">0.0</span>, g);</td>
      </tr>
      <tr>
        <td id="L77" class="blob-num js-line-number" data-line-number="77"></td>
        <td id="LC77" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L78" class="blob-num js-line-number" data-line-number="78"></td>
        <td id="LC78" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... H</span></td>
      </tr>
      <tr>
        <td id="L79" class="blob-num js-line-number" data-line-number="79"></td>
        <td id="LC79" class="blob-code blob-code-inner js-file-line">    H.<span class="pl-c1">setZero</span>();</td>
      </tr>
      <tr>
        <td id="L80" class="blob-num js-line-number" data-line-number="80"></td>
        <td id="LC80" class="blob-code blob-code-inner js-file-line">    H.<span class="pl-c1">topLeftCorner</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>).<span class="pl-c1">setIdentity</span>();</td>
      </tr>
      <tr>
        <td id="L81" class="blob-num js-line-number" data-line-number="81"></td>
        <td id="LC81" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L82" class="blob-num js-line-number" data-line-number="82"></td>
        <td id="LC82" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> first order correlation + white noise, tau = time constant for correlation</span></td>
      </tr>
      <tr>
        <td id="L83" class="blob-num js-line-number" data-line-number="83"></td>
        <td id="LC83" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> gain on white noise plus gain on correlation</span></td>
      </tr>
      <tr>
        <td id="L84" class="blob-num js-line-number" data-line-number="84"></td>
        <td id="LC84" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Rw small - trust time update, Rw more - lean on measurement update</span></td>
      </tr>
      <tr>
        <td id="L85" class="blob-num js-line-number" data-line-number="85"></td>
        <td id="LC85" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> split between accels and gyros and / or noise and correlation</span></td>
      </tr>
      <tr>
        <td id="L86" class="blob-num js-line-number" data-line-number="86"></td>
        <td id="LC86" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... Rw</span></td>
      </tr>
      <tr>
        <td id="L87" class="blob-num js-line-number" data-line-number="87"></td>
        <td id="LC87" class="blob-code blob-code-inner js-file-line">    Rw.<span class="pl-c1">setZero</span>();</td>
      </tr>
      <tr>
        <td id="L88" class="blob-num js-line-number" data-line-number="88"></td>
        <td id="LC88" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">Rw</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>) = config.<span class="pl-smi">sig_w_ax</span>*config.<span class="pl-smi">sig_w_ax</span>;	<span class="pl-c1">Rw</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>) = config.<span class="pl-smi">sig_w_ay</span>*config.<span class="pl-smi">sig_w_ay</span>;	      <span class="pl-c1">Rw</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>) = config.<span class="pl-smi">sig_w_az</span>*config.<span class="pl-smi">sig_w_az</span>; <span class="pl-c"><span class="pl-c">//</span>1 sigma on noise</span></td>
      </tr>
      <tr>
        <td id="L89" class="blob-num js-line-number" data-line-number="89"></td>
        <td id="LC89" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">Rw</span>(<span class="pl-c1">3</span>,<span class="pl-c1">3</span>) = config.<span class="pl-smi">sig_w_gx</span>*config.<span class="pl-smi">sig_w_gx</span>;	<span class="pl-c1">Rw</span>(<span class="pl-c1">4</span>,<span class="pl-c1">4</span>) = config.<span class="pl-smi">sig_w_gy</span>*config.<span class="pl-smi">sig_w_gy</span>;	      <span class="pl-c1">Rw</span>(<span class="pl-c1">5</span>,<span class="pl-c1">5</span>) = config.<span class="pl-smi">sig_w_gz</span>*config.<span class="pl-smi">sig_w_gz</span>;</td>
      </tr>
      <tr>
        <td id="L90" class="blob-num js-line-number" data-line-number="90"></td>
        <td id="LC90" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">Rw</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>) = <span class="pl-c1">2</span>*config.<span class="pl-smi">sig_a_d</span>*config.<span class="pl-smi">sig_a_d</span>/config.<span class="pl-smi">tau_a</span>;	<span class="pl-c1">Rw</span>(<span class="pl-c1">7</span>,<span class="pl-c1">7</span>) = <span class="pl-c1">2</span>*config.<span class="pl-smi">sig_a_d</span>*config.<span class="pl-smi">sig_a_d</span>/config.<span class="pl-smi">tau_a</span>;    <span class="pl-c1">Rw</span>(<span class="pl-c1">8</span>,<span class="pl-c1">8</span>) = <span class="pl-c1">2</span>*config.<span class="pl-smi">sig_a_d</span>*config.<span class="pl-smi">sig_a_d</span>/config.<span class="pl-smi">tau_a</span>;</td>
      </tr>
      <tr>
        <td id="L91" class="blob-num js-line-number" data-line-number="91"></td>
        <td id="LC91" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">Rw</span>(<span class="pl-c1">9</span>,<span class="pl-c1">9</span>) = <span class="pl-c1">2</span>*config.<span class="pl-smi">sig_g_d</span>*config.<span class="pl-smi">sig_g_d</span>/config.<span class="pl-smi">tau_g</span>;	<span class="pl-c1">Rw</span>(<span class="pl-c1">10</span>,<span class="pl-c1">10</span>) = <span class="pl-c1">2</span>*config.<span class="pl-smi">sig_g_d</span>*config.<span class="pl-smi">sig_g_d</span>/config.<span class="pl-smi">tau_g</span>;  <span class="pl-c1">Rw</span>(<span class="pl-c1">11</span>,<span class="pl-c1">11</span>) = <span class="pl-c1">2</span>*config.<span class="pl-smi">sig_g_d</span>*config.<span class="pl-smi">sig_g_d</span>/config.<span class="pl-smi">tau_g</span>;</td>
      </tr>
      <tr>
        <td id="L92" class="blob-num js-line-number" data-line-number="92"></td>
        <td id="LC92" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L93" class="blob-num js-line-number" data-line-number="93"></td>
        <td id="LC93" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... P (initial)</span></td>
      </tr>
      <tr>
        <td id="L94" class="blob-num js-line-number" data-line-number="94"></td>
        <td id="LC94" class="blob-code blob-code-inner js-file-line">    P.<span class="pl-c1">setZero</span>();</td>
      </tr>
      <tr>
        <td id="L95" class="blob-num js-line-number" data-line-number="95"></td>
        <td id="LC95" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">P</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>) = P_P_INIT*P_P_INIT; 	<span class="pl-c1">P</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>) = P_P_INIT*P_P_INIT; 	      <span class="pl-c1">P</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>) = P_P_INIT*P_P_INIT;</td>
      </tr>
      <tr>
        <td id="L96" class="blob-num js-line-number" data-line-number="96"></td>
        <td id="LC96" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">P</span>(<span class="pl-c1">3</span>,<span class="pl-c1">3</span>) = P_V_INIT*P_V_INIT; 	<span class="pl-c1">P</span>(<span class="pl-c1">4</span>,<span class="pl-c1">4</span>) = P_V_INIT*P_V_INIT; 	      <span class="pl-c1">P</span>(<span class="pl-c1">5</span>,<span class="pl-c1">5</span>) = P_V_INIT*P_V_INIT;</td>
      </tr>
      <tr>
        <td id="L97" class="blob-num js-line-number" data-line-number="97"></td>
        <td id="LC97" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">P</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>) = P_A_INIT*P_A_INIT; 	<span class="pl-c1">P</span>(<span class="pl-c1">7</span>,<span class="pl-c1">7</span>) = P_A_INIT*P_A_INIT; 	      <span class="pl-c1">P</span>(<span class="pl-c1">8</span>,<span class="pl-c1">8</span>) = P_HDG_INIT*P_HDG_INIT;</td>
      </tr>
      <tr>
        <td id="L98" class="blob-num js-line-number" data-line-number="98"></td>
        <td id="LC98" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">P</span>(<span class="pl-c1">9</span>,<span class="pl-c1">9</span>) = P_AB_INIT*P_AB_INIT; 	<span class="pl-c1">P</span>(<span class="pl-c1">10</span>,<span class="pl-c1">10</span>) = P_AB_INIT*P_AB_INIT;       <span class="pl-c1">P</span>(<span class="pl-c1">11</span>,<span class="pl-c1">11</span>) = P_AB_INIT*P_AB_INIT;</td>
      </tr>
      <tr>
        <td id="L99" class="blob-num js-line-number" data-line-number="99"></td>
        <td id="LC99" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">P</span>(<span class="pl-c1">12</span>,<span class="pl-c1">12</span>) = P_GB_INIT*P_GB_INIT; 	<span class="pl-c1">P</span>(<span class="pl-c1">13</span>,<span class="pl-c1">13</span>) = P_GB_INIT*P_GB_INIT;       <span class="pl-c1">P</span>(<span class="pl-c1">14</span>,<span class="pl-c1">14</span>) = P_GB_INIT*P_GB_INIT;</td>
      </tr>
      <tr>
        <td id="L100" class="blob-num js-line-number" data-line-number="100"></td>
        <td id="LC100" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L101" class="blob-num js-line-number" data-line-number="101"></td>
        <td id="LC101" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... R</span></td>
      </tr>
      <tr>
        <td id="L102" class="blob-num js-line-number" data-line-number="102"></td>
        <td id="LC102" class="blob-code blob-code-inner js-file-line">    R.<span class="pl-c1">setZero</span>();</td>
      </tr>
      <tr>
        <td id="L103" class="blob-num js-line-number" data-line-number="103"></td>
        <td id="LC103" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">R</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>) = config.<span class="pl-smi">sig_gps_p_ne</span>*config.<span class="pl-smi">sig_gps_p_ne</span>;	 <span class="pl-c1">R</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>) = config.<span class="pl-smi">sig_gps_p_ne</span>*config.<span class="pl-smi">sig_gps_p_ne</span>;  <span class="pl-c1">R</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>) = config.<span class="pl-smi">sig_gps_p_d</span>*config.<span class="pl-smi">sig_gps_p_d</span>;</td>
      </tr>
      <tr>
        <td id="L104" class="blob-num js-line-number" data-line-number="104"></td>
        <td id="LC104" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">R</span>(<span class="pl-c1">3</span>,<span class="pl-c1">3</span>) = config.<span class="pl-smi">sig_gps_v_ne</span>*config.<span class="pl-smi">sig_gps_v_ne</span>;	 <span class="pl-c1">R</span>(<span class="pl-c1">4</span>,<span class="pl-c1">4</span>) = config.<span class="pl-smi">sig_gps_v_ne</span>*config.<span class="pl-smi">sig_gps_v_ne</span>;  <span class="pl-c1">R</span>(<span class="pl-c1">5</span>,<span class="pl-c1">5</span>) = config.<span class="pl-smi">sig_gps_v_d</span>*config.<span class="pl-smi">sig_gps_v_d</span>;</td>
      </tr>
      <tr>
        <td id="L105" class="blob-num js-line-number" data-line-number="105"></td>
        <td id="LC105" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L106" class="blob-num js-line-number" data-line-number="106"></td>
        <td id="LC106" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... update P in get_nav</span></td>
      </tr>
      <tr>
        <td id="L107" class="blob-num js-line-number" data-line-number="107"></td>
        <td id="LC107" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pp0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);	  nav.<span class="pl-smi">Pp1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);	nav.<span class="pl-smi">Pp2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L108" class="blob-num js-line-number" data-line-number="108"></td>
        <td id="LC108" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pv0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">3</span>,<span class="pl-c1">3</span>);	  nav.<span class="pl-smi">Pv1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">4</span>,<span class="pl-c1">4</span>);	nav.<span class="pl-smi">Pv2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">5</span>,<span class="pl-c1">5</span>);</td>
      </tr>
      <tr>
        <td id="L109" class="blob-num js-line-number" data-line-number="109"></td>
        <td id="LC109" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pa0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>);	  nav.<span class="pl-smi">Pa1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">7</span>,<span class="pl-c1">7</span>);	nav.<span class="pl-smi">Pa2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">8</span>,<span class="pl-c1">8</span>);</td>
      </tr>
      <tr>
        <td id="L110" class="blob-num js-line-number" data-line-number="110"></td>
        <td id="LC110" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L111" class="blob-num js-line-number" data-line-number="111"></td>
        <td id="LC111" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pabx</span> = <span class="pl-c1">P</span>(<span class="pl-c1">9</span>,<span class="pl-c1">9</span>);	  nav.<span class="pl-smi">Paby</span> = <span class="pl-c1">P</span>(<span class="pl-c1">10</span>,<span class="pl-c1">10</span>);	nav.<span class="pl-smi">Pabz</span> = <span class="pl-c1">P</span>(<span class="pl-c1">11</span>,<span class="pl-c1">11</span>);</td>
      </tr>
      <tr>
        <td id="L112" class="blob-num js-line-number" data-line-number="112"></td>
        <td id="LC112" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pgbx</span> = <span class="pl-c1">P</span>(<span class="pl-c1">12</span>,<span class="pl-c1">12</span>);  nav.<span class="pl-smi">Pgby</span> = <span class="pl-c1">P</span>(<span class="pl-c1">13</span>,<span class="pl-c1">13</span>);  nav.<span class="pl-smi">Pgbz</span> = <span class="pl-c1">P</span>(<span class="pl-c1">14</span>,<span class="pl-c1">14</span>);</td>
      </tr>
      <tr>
        <td id="L113" class="blob-num js-line-number" data-line-number="113"></td>
        <td id="LC113" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L114" class="blob-num js-line-number" data-line-number="114"></td>
        <td id="LC114" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> .. then initialize states with GPS Data</span></td>
      </tr>
      <tr>
        <td id="L115" class="blob-num js-line-number" data-line-number="115"></td>
        <td id="LC115" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">lat</span> = gps.<span class="pl-smi">lat</span>*D2R;</td>
      </tr>
      <tr>
        <td id="L116" class="blob-num js-line-number" data-line-number="116"></td>
        <td id="LC116" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">lon</span> = gps.<span class="pl-smi">lon</span>*D2R;</td>
      </tr>
      <tr>
        <td id="L117" class="blob-num js-line-number" data-line-number="117"></td>
        <td id="LC117" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">alt</span> = gps.<span class="pl-smi">alt</span>;</td>
      </tr>
      <tr>
        <td id="L118" class="blob-num js-line-number" data-line-number="118"></td>
        <td id="LC118" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L119" class="blob-num js-line-number" data-line-number="119"></td>
        <td id="LC119" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">vn</span> = gps.<span class="pl-smi">vn</span>;</td>
      </tr>
      <tr>
        <td id="L120" class="blob-num js-line-number" data-line-number="120"></td>
        <td id="LC120" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">ve</span> = gps.<span class="pl-smi">ve</span>;</td>
      </tr>
      <tr>
        <td id="L121" class="blob-num js-line-number" data-line-number="121"></td>
        <td id="LC121" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">vd</span> = gps.<span class="pl-smi">vd</span>;</td>
      </tr>
      <tr>
        <td id="L122" class="blob-num js-line-number" data-line-number="122"></td>
        <td id="LC122" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L123" class="blob-num js-line-number" data-line-number="123"></td>
        <td id="LC123" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... and initialize states with IMU Data, theta from Ax, aircraft</span></td>
      </tr>
      <tr>
        <td id="L124" class="blob-num js-line-number" data-line-number="124"></td>
        <td id="LC124" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> at rest</span></td>
      </tr>
      <tr>
        <td id="L125" class="blob-num js-line-number" data-line-number="125"></td>
        <td id="LC125" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">the</span> = <span class="pl-c1">asin</span>(imu.<span class="pl-smi">ax</span>/g); </td>
      </tr>
      <tr>
        <td id="L126" class="blob-num js-line-number" data-line-number="126"></td>
        <td id="LC126" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> phi from Ay, aircraft at rest</span></td>
      </tr>
      <tr>
        <td id="L127" class="blob-num js-line-number" data-line-number="127"></td>
        <td id="LC127" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">phi</span> = <span class="pl-c1">asin</span>(imu.<span class="pl-smi">ay</span>/(g*<span class="pl-c1">cos</span>(nav.<span class="pl-smi">the</span>))); </td>
      </tr>
      <tr>
        <td id="L128" class="blob-num js-line-number" data-line-number="128"></td>
        <td id="LC128" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">psi</span> = <span class="pl-c1">90</span>*D2R - <span class="pl-c1">atan2</span>(imu.<span class="pl-smi">hx</span>, imu.<span class="pl-smi">hy</span>);</td>
      </tr>
      <tr>
        <td id="L129" class="blob-num js-line-number" data-line-number="129"></td>
        <td id="LC129" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L130" class="blob-num js-line-number" data-line-number="130"></td>
        <td id="LC130" class="blob-code blob-code-inner js-file-line">    quat = <span class="pl-c1">eul2quat</span>(nav.<span class="pl-smi">phi</span>, nav.<span class="pl-smi">the</span>, nav.<span class="pl-smi">psi</span>);</td>
      </tr>
      <tr>
        <td id="L131" class="blob-num js-line-number" data-line-number="131"></td>
        <td id="LC131" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qw</span> = quat.<span class="pl-c1">w</span>();</td>
      </tr>
      <tr>
        <td id="L132" class="blob-num js-line-number" data-line-number="132"></td>
        <td id="LC132" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qx</span> = quat.<span class="pl-c1">x</span>();</td>
      </tr>
      <tr>
        <td id="L133" class="blob-num js-line-number" data-line-number="133"></td>
        <td id="LC133" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qy</span> = quat.<span class="pl-c1">y</span>();</td>
      </tr>
      <tr>
        <td id="L134" class="blob-num js-line-number" data-line-number="134"></td>
        <td id="LC134" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qz</span> = quat.<span class="pl-c1">z</span>();</td>
      </tr>
      <tr>
        <td id="L135" class="blob-num js-line-number" data-line-number="135"></td>
        <td id="LC135" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L136" class="blob-num js-line-number" data-line-number="136"></td>
        <td id="LC136" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">abx</span> = <span class="pl-c1">0.0</span>;</td>
      </tr>
      <tr>
        <td id="L137" class="blob-num js-line-number" data-line-number="137"></td>
        <td id="LC137" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">aby</span> = <span class="pl-c1">0.0</span>; </td>
      </tr>
      <tr>
        <td id="L138" class="blob-num js-line-number" data-line-number="138"></td>
        <td id="LC138" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">abz</span> = <span class="pl-c1">0.0</span>;</td>
      </tr>
      <tr>
        <td id="L139" class="blob-num js-line-number" data-line-number="139"></td>
        <td id="LC139" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L140" class="blob-num js-line-number" data-line-number="140"></td>
        <td id="LC140" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">gbx</span> = imu.<span class="pl-smi">p</span>;</td>
      </tr>
      <tr>
        <td id="L141" class="blob-num js-line-number" data-line-number="141"></td>
        <td id="LC141" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">gby</span> = imu.<span class="pl-smi">q</span>;</td>
      </tr>
      <tr>
        <td id="L142" class="blob-num js-line-number" data-line-number="142"></td>
        <td id="LC142" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">gbz</span> = imu.<span class="pl-smi">r</span>;</td>
      </tr>
      <tr>
        <td id="L143" class="blob-num js-line-number" data-line-number="143"></td>
        <td id="LC143" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L144" class="blob-num js-line-number" data-line-number="144"></td>
        <td id="LC144" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Specific forces and Rotation Rate</span></td>
      </tr>
      <tr>
        <td id="L145" class="blob-num js-line-number" data-line-number="145"></td>
        <td id="LC145" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">f_b</span>(<span class="pl-c1">0</span>) = imu.<span class="pl-smi">ax</span> - nav.<span class="pl-smi">abx</span>;</td>
      </tr>
      <tr>
        <td id="L146" class="blob-num js-line-number" data-line-number="146"></td>
        <td id="LC146" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">f_b</span>(<span class="pl-c1">1</span>) = imu.<span class="pl-smi">ay</span> - nav.<span class="pl-smi">aby</span>;</td>
      </tr>
      <tr>
        <td id="L147" class="blob-num js-line-number" data-line-number="147"></td>
        <td id="LC147" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">f_b</span>(<span class="pl-c1">2</span>) = imu.<span class="pl-smi">az</span> - nav.<span class="pl-smi">abz</span>;</td>
      </tr>
      <tr>
        <td id="L148" class="blob-num js-line-number" data-line-number="148"></td>
        <td id="LC148" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L149" class="blob-num js-line-number" data-line-number="149"></td>
        <td id="LC149" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">om_ib</span>(<span class="pl-c1">0</span>) = imu.<span class="pl-smi">p</span> - nav.<span class="pl-smi">gbx</span>;</td>
      </tr>
      <tr>
        <td id="L150" class="blob-num js-line-number" data-line-number="150"></td>
        <td id="LC150" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">om_ib</span>(<span class="pl-c1">1</span>) = imu.<span class="pl-smi">q</span> - nav.<span class="pl-smi">gby</span>;</td>
      </tr>
      <tr>
        <td id="L151" class="blob-num js-line-number" data-line-number="151"></td>
        <td id="LC151" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">om_ib</span>(<span class="pl-c1">2</span>) = imu.<span class="pl-smi">r</span> - nav.<span class="pl-smi">gbz</span>;</td>
      </tr>
      <tr>
        <td id="L152" class="blob-num js-line-number" data-line-number="152"></td>
        <td id="LC152" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L153" class="blob-num js-line-number" data-line-number="153"></td>
        <td id="LC153" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Time during initialization</span></td>
      </tr>
      <tr>
        <td id="L154" class="blob-num js-line-number" data-line-number="154"></td>
        <td id="LC154" class="blob-code blob-code-inner js-file-line">    tprev = imu.<span class="pl-smi">time</span>;</td>
      </tr>
      <tr>
        <td id="L155" class="blob-num js-line-number" data-line-number="155"></td>
        <td id="LC155" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L156" class="blob-num js-line-number" data-line-number="156"></td>
        <td id="LC156" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span>nav.init = 1;</span></td>
      </tr>
      <tr>
        <td id="L157" class="blob-num js-line-number" data-line-number="157"></td>
        <td id="LC157" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">time</span> = imu.<span class="pl-smi">time</span>;</td>
      </tr>
      <tr>
        <td id="L158" class="blob-num js-line-number" data-line-number="158"></td>
        <td id="LC158" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">err_type</span> = data_valid;</td>
      </tr>
      <tr>
        <td id="L159" class="blob-num js-line-number" data-line-number="159"></td>
        <td id="LC159" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L160" class="blob-num js-line-number" data-line-number="160"></td>
        <td id="LC160" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">return</span> nav;</td>
      </tr>
      <tr>
        <td id="L161" class="blob-num js-line-number" data-line-number="161"></td>
        <td id="LC161" class="blob-code blob-code-inner js-file-line">}</td>
      </tr>
      <tr>
        <td id="L162" class="blob-num js-line-number" data-line-number="162"></td>
        <td id="LC162" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L163" class="blob-num js-line-number" data-line-number="163"></td>
        <td id="LC163" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> Main get_nav filter function</span></td>
      </tr>
      <tr>
        <td id="L164" class="blob-num js-line-number" data-line-number="164"></td>
        <td id="LC164" class="blob-code blob-code-inner js-file-line">NAVdata <span class="pl-en">EKF15::update</span>(IMUdata imu, GPSdata gps) {</td>
      </tr>
      <tr>
        <td id="L165" class="blob-num js-line-number" data-line-number="165"></td>
        <td id="LC165" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> compute time-elapsed &#39;dt&#39;</span></td>
      </tr>
      <tr>
        <td id="L166" class="blob-num js-line-number" data-line-number="166"></td>
        <td id="LC166" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> This compute the navigation state at the DAQ&#39;s Time Stamp</span></td>
      </tr>
      <tr>
        <td id="L167" class="blob-num js-line-number" data-line-number="167"></td>
        <td id="LC167" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">double</span> tnow = imu.<span class="pl-smi">time</span>;</td>
      </tr>
      <tr>
        <td id="L168" class="blob-num js-line-number" data-line-number="168"></td>
        <td id="LC168" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">double</span> imu_dt = tnow - tprev;</td>
      </tr>
      <tr>
        <td id="L169" class="blob-num js-line-number" data-line-number="169"></td>
        <td id="LC169" class="blob-code blob-code-inner js-file-line">    tprev = tnow;		</td>
      </tr>
      <tr>
        <td id="L170" class="blob-num js-line-number" data-line-number="170"></td>
        <td id="LC170" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L171" class="blob-num js-line-number" data-line-number="171"></td>
        <td id="LC171" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ==================  Time Update  ===================</span></td>
      </tr>
      <tr>
        <td id="L172" class="blob-num js-line-number" data-line-number="172"></td>
        <td id="LC172" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L173" class="blob-num js-line-number" data-line-number="173"></td>
        <td id="LC173" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> AHRS Transformations</span></td>
      </tr>
      <tr>
        <td id="L174" class="blob-num js-line-number" data-line-number="174"></td>
        <td id="LC174" class="blob-code blob-code-inner js-file-line">    C_N2B = <span class="pl-c1">quat2dcm</span>(quat);</td>
      </tr>
      <tr>
        <td id="L175" class="blob-num js-line-number" data-line-number="175"></td>
        <td id="LC175" class="blob-code blob-code-inner js-file-line">    C_B2N = C_N2B.<span class="pl-c1">transpose</span>();</td>
      </tr>
      <tr>
        <td id="L176" class="blob-num js-line-number" data-line-number="176"></td>
        <td id="LC176" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L177" class="blob-num js-line-number" data-line-number="177"></td>
        <td id="LC177" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Attitude Update</span></td>
      </tr>
      <tr>
        <td id="L178" class="blob-num js-line-number" data-line-number="178"></td>
        <td id="LC178" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... Calculate Navigation Rate</span></td>
      </tr>
      <tr>
        <td id="L179" class="blob-num js-line-number" data-line-number="179"></td>
        <td id="LC179" class="blob-code blob-code-inner js-file-line">    Vector3d <span class="pl-smi">vel_vec</span>(nav.<span class="pl-smi">vn</span>, nav.<span class="pl-smi">ve</span>, nav.<span class="pl-smi">vd</span>);</td>
      </tr>
      <tr>
        <td id="L180" class="blob-num js-line-number" data-line-number="180"></td>
        <td id="LC180" class="blob-code blob-code-inner js-file-line">    Vector3d <span class="pl-smi">pos_vec</span>(nav.<span class="pl-smi">lat</span>, nav.<span class="pl-smi">lon</span>, nav.<span class="pl-smi">alt</span>);</td>
      </tr>
      <tr>
        <td id="L181" class="blob-num js-line-number" data-line-number="181"></td>
        <td id="LC181" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L182" class="blob-num js-line-number" data-line-number="182"></td>
        <td id="LC182" class="blob-code blob-code-inner js-file-line">    nr = <span class="pl-c1">navrate</span>(vel_vec,pos_vec);  <span class="pl-c"><span class="pl-c">/*</span> note: unused, llarate used instead <span class="pl-c">*/</span></span></td>
      </tr>
      <tr>
        <td id="L183" class="blob-num js-line-number" data-line-number="183"></td>
        <td id="LC183" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L184" class="blob-num js-line-number" data-line-number="184"></td>
        <td id="LC184" class="blob-code blob-code-inner js-file-line">    Quaterniond dq;</td>
      </tr>
      <tr>
        <td id="L185" class="blob-num js-line-number" data-line-number="185"></td>
        <td id="LC185" class="blob-code blob-code-inner js-file-line">    dq = <span class="pl-c1">Quaterniond</span>(<span class="pl-c1">1.0</span>, <span class="pl-c1">0.5</span>*<span class="pl-c1">om_ib</span>(<span class="pl-c1">0</span>)*imu_dt, <span class="pl-c1">0.5</span>*<span class="pl-c1">om_ib</span>(<span class="pl-c1">1</span>)*imu_dt, <span class="pl-c1">0.5</span>*<span class="pl-c1">om_ib</span>(<span class="pl-c1">2</span>)*imu_dt);</td>
      </tr>
      <tr>
        <td id="L186" class="blob-num js-line-number" data-line-number="186"></td>
        <td id="LC186" class="blob-code blob-code-inner js-file-line">    quat = (quat * dq).<span class="pl-c1">normalized</span>();</td>
      </tr>
      <tr>
        <td id="L187" class="blob-num js-line-number" data-line-number="187"></td>
        <td id="LC187" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L188" class="blob-num js-line-number" data-line-number="188"></td>
        <td id="LC188" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">if</span> (quat.<span class="pl-c1">w</span>() &lt; <span class="pl-c1">0</span>) {</td>
      </tr>
      <tr>
        <td id="L189" class="blob-num js-line-number" data-line-number="189"></td>
        <td id="LC189" class="blob-code blob-code-inner js-file-line">        <span class="pl-c"><span class="pl-c">//</span> Avoid quaternion flips sign</span></td>
      </tr>
      <tr>
        <td id="L190" class="blob-num js-line-number" data-line-number="190"></td>
        <td id="LC190" class="blob-code blob-code-inner js-file-line">        quat = <span class="pl-c1">Quaterniond</span>(-quat.<span class="pl-c1">w</span>(), -quat.<span class="pl-c1">x</span>(), -quat.<span class="pl-c1">y</span>(), -quat.<span class="pl-c1">z</span>());</td>
      </tr>
      <tr>
        <td id="L191" class="blob-num js-line-number" data-line-number="191"></td>
        <td id="LC191" class="blob-code blob-code-inner js-file-line">    }</td>
      </tr>
      <tr>
        <td id="L192" class="blob-num js-line-number" data-line-number="192"></td>
        <td id="LC192" class="blob-code blob-code-inner js-file-line">    </td>
      </tr>
      <tr>
        <td id="L193" class="blob-num js-line-number" data-line-number="193"></td>
        <td id="LC193" class="blob-code blob-code-inner js-file-line">    Vector3d att_vec = <span class="pl-c1">quat2eul</span>(quat);</td>
      </tr>
      <tr>
        <td id="L194" class="blob-num js-line-number" data-line-number="194"></td>
        <td id="LC194" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">phi</span> = <span class="pl-c1">att_vec</span>(<span class="pl-c1">0</span>);</td>
      </tr>
      <tr>
        <td id="L195" class="blob-num js-line-number" data-line-number="195"></td>
        <td id="LC195" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">the</span> = <span class="pl-c1">att_vec</span>(<span class="pl-c1">1</span>);</td>
      </tr>
      <tr>
        <td id="L196" class="blob-num js-line-number" data-line-number="196"></td>
        <td id="LC196" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">psi</span> = <span class="pl-c1">att_vec</span>(<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L197" class="blob-num js-line-number" data-line-number="197"></td>
        <td id="LC197" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L198" class="blob-num js-line-number" data-line-number="198"></td>
        <td id="LC198" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Velocity Update</span></td>
      </tr>
      <tr>
        <td id="L199" class="blob-num js-line-number" data-line-number="199"></td>
        <td id="LC199" class="blob-code blob-code-inner js-file-line">    dx = C_B2N * f_b;</td>
      </tr>
      <tr>
        <td id="L200" class="blob-num js-line-number" data-line-number="200"></td>
        <td id="LC200" class="blob-code blob-code-inner js-file-line">    dx += grav;</td>
      </tr>
      <tr>
        <td id="L201" class="blob-num js-line-number" data-line-number="201"></td>
        <td id="LC201" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L202" class="blob-num js-line-number" data-line-number="202"></td>
        <td id="LC202" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">vn</span> += imu_dt*<span class="pl-c1">dx</span>(<span class="pl-c1">0</span>);</td>
      </tr>
      <tr>
        <td id="L203" class="blob-num js-line-number" data-line-number="203"></td>
        <td id="LC203" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">ve</span> += imu_dt*<span class="pl-c1">dx</span>(<span class="pl-c1">1</span>);</td>
      </tr>
      <tr>
        <td id="L204" class="blob-num js-line-number" data-line-number="204"></td>
        <td id="LC204" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">vd</span> += imu_dt*<span class="pl-c1">dx</span>(<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L205" class="blob-num js-line-number" data-line-number="205"></td>
        <td id="LC205" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L206" class="blob-num js-line-number" data-line-number="206"></td>
        <td id="LC206" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Position Update</span></td>
      </tr>
      <tr>
        <td id="L207" class="blob-num js-line-number" data-line-number="207"></td>
        <td id="LC207" class="blob-code blob-code-inner js-file-line">    dx = <span class="pl-c1">llarate</span>(vel_vec, pos_vec);</td>
      </tr>
      <tr>
        <td id="L208" class="blob-num js-line-number" data-line-number="208"></td>
        <td id="LC208" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">lat</span> += imu_dt*<span class="pl-c1">dx</span>(<span class="pl-c1">0</span>);</td>
      </tr>
      <tr>
        <td id="L209" class="blob-num js-line-number" data-line-number="209"></td>
        <td id="LC209" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">lon</span> += imu_dt*<span class="pl-c1">dx</span>(<span class="pl-c1">1</span>);</td>
      </tr>
      <tr>
        <td id="L210" class="blob-num js-line-number" data-line-number="210"></td>
        <td id="LC210" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">alt</span> += imu_dt*<span class="pl-c1">dx</span>(<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L211" class="blob-num js-line-number" data-line-number="211"></td>
        <td id="LC211" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L212" class="blob-num js-line-number" data-line-number="212"></td>
        <td id="LC212" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> JACOBIAN</span></td>
      </tr>
      <tr>
        <td id="L213" class="blob-num js-line-number" data-line-number="213"></td>
        <td id="LC213" class="blob-code blob-code-inner js-file-line">    F.<span class="pl-c1">setZero</span>();</td>
      </tr>
      <tr>
        <td id="L214" class="blob-num js-line-number" data-line-number="214"></td>
        <td id="LC214" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... pos2gs</span></td>
      </tr>
      <tr>
        <td id="L215" class="blob-num js-line-number" data-line-number="215"></td>
        <td id="LC215" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">0</span>,<span class="pl-c1">3</span>) = <span class="pl-c1">1.0</span>; 	<span class="pl-c1">F</span>(<span class="pl-c1">1</span>,<span class="pl-c1">4</span>) = <span class="pl-c1">1.0</span>; 	<span class="pl-c1">F</span>(<span class="pl-c1">2</span>,<span class="pl-c1">5</span>) = <span class="pl-c1">1.0</span>;</td>
      </tr>
      <tr>
        <td id="L216" class="blob-num js-line-number" data-line-number="216"></td>
        <td id="LC216" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... gs2pos</span></td>
      </tr>
      <tr>
        <td id="L217" class="blob-num js-line-number" data-line-number="217"></td>
        <td id="LC217" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">2</span>) = -<span class="pl-c1">2</span> * g / EARTH_RADIUS;</td>
      </tr>
      <tr>
        <td id="L218" class="blob-num js-line-number" data-line-number="218"></td>
        <td id="LC218" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L219" class="blob-num js-line-number" data-line-number="219"></td>
        <td id="LC219" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... gs2att</span></td>
      </tr>
      <tr>
        <td id="L220" class="blob-num js-line-number" data-line-number="220"></td>
        <td id="LC220" class="blob-code blob-code-inner js-file-line">    temp33 = C_B2N * <span class="pl-c1">sk</span>(f_b);</td>
      </tr>
      <tr>
        <td id="L221" class="blob-num js-line-number" data-line-number="221"></td>
        <td id="LC221" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L222" class="blob-num js-line-number" data-line-number="222"></td>
        <td id="LC222" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">3</span>,<span class="pl-c1">6</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">3</span>,<span class="pl-c1">7</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">0</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">3</span>,<span class="pl-c1">8</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">0</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L223" class="blob-num js-line-number" data-line-number="223"></td>
        <td id="LC223" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">4</span>,<span class="pl-c1">6</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">1</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">4</span>,<span class="pl-c1">7</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">4</span>,<span class="pl-c1">8</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">1</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L224" class="blob-num js-line-number" data-line-number="224"></td>
        <td id="LC224" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">6</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">2</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">7</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">2</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">8</span>) = -<span class="pl-c1">2.0</span>*<span class="pl-c1">temp33</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L225" class="blob-num js-line-number" data-line-number="225"></td>
        <td id="LC225" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L226" class="blob-num js-line-number" data-line-number="226"></td>
        <td id="LC226" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... gs2acc</span></td>
      </tr>
      <tr>
        <td id="L227" class="blob-num js-line-number" data-line-number="227"></td>
        <td id="LC227" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">3</span>,<span class="pl-c1">9</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">3</span>,<span class="pl-c1">10</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">0</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">3</span>,<span class="pl-c1">11</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">0</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L228" class="blob-num js-line-number" data-line-number="228"></td>
        <td id="LC228" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">4</span>,<span class="pl-c1">9</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">1</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">4</span>,<span class="pl-c1">10</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">4</span>,<span class="pl-c1">11</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">1</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L229" class="blob-num js-line-number" data-line-number="229"></td>
        <td id="LC229" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">9</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">2</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">10</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">2</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">5</span>,<span class="pl-c1">11</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L230" class="blob-num js-line-number" data-line-number="230"></td>
        <td id="LC230" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L231" class="blob-num js-line-number" data-line-number="231"></td>
        <td id="LC231" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... att2att</span></td>
      </tr>
      <tr>
        <td id="L232" class="blob-num js-line-number" data-line-number="232"></td>
        <td id="LC232" class="blob-code blob-code-inner js-file-line">    temp33 = <span class="pl-c1">sk</span>(om_ib);</td>
      </tr>
      <tr>
        <td id="L233" class="blob-num js-line-number" data-line-number="233"></td>
        <td id="LC233" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">6</span>,<span class="pl-c1">7</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">0</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">6</span>,<span class="pl-c1">8</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">0</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L234" class="blob-num js-line-number" data-line-number="234"></td>
        <td id="LC234" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">7</span>,<span class="pl-c1">6</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">1</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">7</span>,<span class="pl-c1">7</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">7</span>,<span class="pl-c1">8</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">1</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L235" class="blob-num js-line-number" data-line-number="235"></td>
        <td id="LC235" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">8</span>,<span class="pl-c1">6</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">2</span>,<span class="pl-c1">0</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">8</span>,<span class="pl-c1">7</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">2</span>,<span class="pl-c1">1</span>);  <span class="pl-c1">F</span>(<span class="pl-c1">8</span>,<span class="pl-c1">8</span>) = -<span class="pl-c1">temp33</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L236" class="blob-num js-line-number" data-line-number="236"></td>
        <td id="LC236" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L237" class="blob-num js-line-number" data-line-number="237"></td>
        <td id="LC237" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... att2gyr</span></td>
      </tr>
      <tr>
        <td id="L238" class="blob-num js-line-number" data-line-number="238"></td>
        <td id="LC238" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">6</span>,<span class="pl-c1">12</span>) = -<span class="pl-c1">0.5</span>;</td>
      </tr>
      <tr>
        <td id="L239" class="blob-num js-line-number" data-line-number="239"></td>
        <td id="LC239" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">7</span>,<span class="pl-c1">13</span>) = -<span class="pl-c1">0.5</span>;</td>
      </tr>
      <tr>
        <td id="L240" class="blob-num js-line-number" data-line-number="240"></td>
        <td id="LC240" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">8</span>,<span class="pl-c1">14</span>) = -<span class="pl-c1">0.5</span>;</td>
      </tr>
      <tr>
        <td id="L241" class="blob-num js-line-number" data-line-number="241"></td>
        <td id="LC241" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L242" class="blob-num js-line-number" data-line-number="242"></td>
        <td id="LC242" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ... Accel Markov Bias</span></td>
      </tr>
      <tr>
        <td id="L243" class="blob-num js-line-number" data-line-number="243"></td>
        <td id="LC243" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">9</span>,<span class="pl-c1">9</span>) = -<span class="pl-c1">1.0</span>/config.<span class="pl-smi">tau_a</span>;    <span class="pl-c1">F</span>(<span class="pl-c1">10</span>,<span class="pl-c1">10</span>) = -<span class="pl-c1">1.0</span>/config.<span class="pl-smi">tau_a</span>;  <span class="pl-c1">F</span>(<span class="pl-c1">11</span>,<span class="pl-c1">11</span>) = -<span class="pl-c1">1.0</span>/config.<span class="pl-smi">tau_a</span>;</td>
      </tr>
      <tr>
        <td id="L244" class="blob-num js-line-number" data-line-number="244"></td>
        <td id="LC244" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">F</span>(<span class="pl-c1">12</span>,<span class="pl-c1">12</span>) = -<span class="pl-c1">1.0</span>/config.<span class="pl-smi">tau_g</span>;  <span class="pl-c1">F</span>(<span class="pl-c1">13</span>,<span class="pl-c1">13</span>) = -<span class="pl-c1">1.0</span>/config.<span class="pl-smi">tau_g</span>;  <span class="pl-c1">F</span>(<span class="pl-c1">14</span>,<span class="pl-c1">14</span>) = -<span class="pl-c1">1.0</span>/config.<span class="pl-smi">tau_g</span>;</td>
      </tr>
      <tr>
        <td id="L245" class="blob-num js-line-number" data-line-number="245"></td>
        <td id="LC245" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L246" class="blob-num js-line-number" data-line-number="246"></td>
        <td id="LC246" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> State Transition Matrix: PHI = I15 + F*dt;</span></td>
      </tr>
      <tr>
        <td id="L247" class="blob-num js-line-number" data-line-number="247"></td>
        <td id="LC247" class="blob-code blob-code-inner js-file-line">    PHI = I15 + F * imu_dt;</td>
      </tr>
      <tr>
        <td id="L248" class="blob-num js-line-number" data-line-number="248"></td>
        <td id="LC248" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L249" class="blob-num js-line-number" data-line-number="249"></td>
        <td id="LC249" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Process Noise</span></td>
      </tr>
      <tr>
        <td id="L250" class="blob-num js-line-number" data-line-number="250"></td>
        <td id="LC250" class="blob-code blob-code-inner js-file-line">    G.<span class="pl-c1">setZero</span>();</td>
      </tr>
      <tr>
        <td id="L251" class="blob-num js-line-number" data-line-number="251"></td>
        <td id="LC251" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">3</span>,<span class="pl-c1">0</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);   <span class="pl-c1">G</span>(<span class="pl-c1">3</span>,<span class="pl-c1">1</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">0</span>,<span class="pl-c1">1</span>);   <span class="pl-c1">G</span>(<span class="pl-c1">3</span>,<span class="pl-c1">2</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">0</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L252" class="blob-num js-line-number" data-line-number="252"></td>
        <td id="LC252" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">4</span>,<span class="pl-c1">0</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">1</span>,<span class="pl-c1">0</span>);   <span class="pl-c1">G</span>(<span class="pl-c1">4</span>,<span class="pl-c1">1</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);   <span class="pl-c1">G</span>(<span class="pl-c1">4</span>,<span class="pl-c1">2</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">1</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L253" class="blob-num js-line-number" data-line-number="253"></td>
        <td id="LC253" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">5</span>,<span class="pl-c1">0</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">2</span>,<span class="pl-c1">0</span>);   <span class="pl-c1">G</span>(<span class="pl-c1">5</span>,<span class="pl-c1">1</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">2</span>,<span class="pl-c1">1</span>);   <span class="pl-c1">G</span>(<span class="pl-c1">5</span>,<span class="pl-c1">2</span>) = -<span class="pl-c1">C_B2N</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L254" class="blob-num js-line-number" data-line-number="254"></td>
        <td id="LC254" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L255" class="blob-num js-line-number" data-line-number="255"></td>
        <td id="LC255" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">6</span>,<span class="pl-c1">3</span>) = -<span class="pl-c1">0.5</span>;</td>
      </tr>
      <tr>
        <td id="L256" class="blob-num js-line-number" data-line-number="256"></td>
        <td id="LC256" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">7</span>,<span class="pl-c1">4</span>) = -<span class="pl-c1">0.5</span>;</td>
      </tr>
      <tr>
        <td id="L257" class="blob-num js-line-number" data-line-number="257"></td>
        <td id="LC257" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">8</span>,<span class="pl-c1">5</span>) = -<span class="pl-c1">0.5</span>;</td>
      </tr>
      <tr>
        <td id="L258" class="blob-num js-line-number" data-line-number="258"></td>
        <td id="LC258" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L259" class="blob-num js-line-number" data-line-number="259"></td>
        <td id="LC259" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">9</span>,<span class="pl-c1">6</span>) = <span class="pl-c1">1.0</span>; 	    <span class="pl-c1">G</span>(<span class="pl-c1">10</span>,<span class="pl-c1">7</span>) = <span class="pl-c1">1.0</span>; 	    <span class="pl-c1">G</span>(<span class="pl-c1">11</span>,<span class="pl-c1">8</span>) = <span class="pl-c1">1.0</span>;</td>
      </tr>
      <tr>
        <td id="L260" class="blob-num js-line-number" data-line-number="260"></td>
        <td id="LC260" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">G</span>(<span class="pl-c1">12</span>,<span class="pl-c1">9</span>) = <span class="pl-c1">1.0</span>; 	    <span class="pl-c1">G</span>(<span class="pl-c1">13</span>,<span class="pl-c1">10</span>) = <span class="pl-c1">1.0</span>; 	    <span class="pl-c1">G</span>(<span class="pl-c1">14</span>,<span class="pl-c1">11</span>) = <span class="pl-c1">1.0</span>;</td>
      </tr>
      <tr>
        <td id="L261" class="blob-num js-line-number" data-line-number="261"></td>
        <td id="LC261" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L262" class="blob-num js-line-number" data-line-number="262"></td>
        <td id="LC262" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Discrete Process Noise</span></td>
      </tr>
      <tr>
        <td id="L263" class="blob-num js-line-number" data-line-number="263"></td>
        <td id="LC263" class="blob-code blob-code-inner js-file-line">    Qw = G * Rw * G.<span class="pl-c1">transpose</span>() * imu_dt;		<span class="pl-c"><span class="pl-c">//</span> Qw = dt*G*Rw*G&#39;</span></td>
      </tr>
      <tr>
        <td id="L264" class="blob-num js-line-number" data-line-number="264"></td>
        <td id="LC264" class="blob-code blob-code-inner js-file-line">    Q = PHI * Qw;					<span class="pl-c"><span class="pl-c">//</span> Q = (I+F*dt)*Qw</span></td>
      </tr>
      <tr>
        <td id="L265" class="blob-num js-line-number" data-line-number="265"></td>
        <td id="LC265" class="blob-code blob-code-inner js-file-line">    Q = (Q + Q.<span class="pl-c1">transpose</span>()) * <span class="pl-c1">0.5</span>;			<span class="pl-c"><span class="pl-c">//</span> Q = 0.5*(Q+Q&#39;)</span></td>
      </tr>
      <tr>
        <td id="L266" class="blob-num js-line-number" data-line-number="266"></td>
        <td id="LC266" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L267" class="blob-num js-line-number" data-line-number="267"></td>
        <td id="LC267" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Covariance Time Update</span></td>
      </tr>
      <tr>
        <td id="L268" class="blob-num js-line-number" data-line-number="268"></td>
        <td id="LC268" class="blob-code blob-code-inner js-file-line">    P = PHI * P * PHI.<span class="pl-c1">transpose</span>() + Q;			<span class="pl-c"><span class="pl-c">//</span> P = PHI*P*PHI&#39; + Q</span></td>
      </tr>
      <tr>
        <td id="L269" class="blob-num js-line-number" data-line-number="269"></td>
        <td id="LC269" class="blob-code blob-code-inner js-file-line">    P = (P + P.<span class="pl-c1">transpose</span>()) * <span class="pl-c1">0.5</span>;			<span class="pl-c"><span class="pl-c">//</span> P = 0.5*(P+P&#39;)</span></td>
      </tr>
      <tr>
        <td id="L270" class="blob-num js-line-number" data-line-number="270"></td>
        <td id="LC270" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L271" class="blob-num js-line-number" data-line-number="271"></td>
        <td id="LC271" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pp0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);     nav.<span class="pl-smi">Pp1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);     nav.<span class="pl-smi">Pp2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L272" class="blob-num js-line-number" data-line-number="272"></td>
        <td id="LC272" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pv0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">3</span>,<span class="pl-c1">3</span>);     nav.<span class="pl-smi">Pv1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">4</span>,<span class="pl-c1">4</span>);     nav.<span class="pl-smi">Pv2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">5</span>,<span class="pl-c1">5</span>);</td>
      </tr>
      <tr>
        <td id="L273" class="blob-num js-line-number" data-line-number="273"></td>
        <td id="LC273" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pa0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>);     nav.<span class="pl-smi">Pa1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">7</span>,<span class="pl-c1">7</span>);     nav.<span class="pl-smi">Pa2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">8</span>,<span class="pl-c1">8</span>);</td>
      </tr>
      <tr>
        <td id="L274" class="blob-num js-line-number" data-line-number="274"></td>
        <td id="LC274" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pabx</span> = <span class="pl-c1">P</span>(<span class="pl-c1">9</span>,<span class="pl-c1">9</span>);    nav.<span class="pl-smi">Paby</span> = <span class="pl-c1">P</span>(<span class="pl-c1">10</span>,<span class="pl-c1">10</span>);  nav.<span class="pl-smi">Pabz</span> = <span class="pl-c1">P</span>(<span class="pl-c1">11</span>,<span class="pl-c1">11</span>);</td>
      </tr>
      <tr>
        <td id="L275" class="blob-num js-line-number" data-line-number="275"></td>
        <td id="LC275" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">Pgbx</span> = <span class="pl-c1">P</span>(<span class="pl-c1">12</span>,<span class="pl-c1">12</span>);  nav.<span class="pl-smi">Pgby</span> = <span class="pl-c1">P</span>(<span class="pl-c1">13</span>,<span class="pl-c1">13</span>);  nav.<span class="pl-smi">Pgbz</span> = <span class="pl-c1">P</span>(<span class="pl-c1">14</span>,<span class="pl-c1">14</span>);</td>
      </tr>
      <tr>
        <td id="L276" class="blob-num js-line-number" data-line-number="276"></td>
        <td id="LC276" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L277" class="blob-num js-line-number" data-line-number="277"></td>
        <td id="LC277" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> ==================  DONE TU  ===================</span></td>
      </tr>
      <tr>
        <td id="L278" class="blob-num js-line-number" data-line-number="278"></td>
        <td id="LC278" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L279" class="blob-num js-line-number" data-line-number="279"></td>
        <td id="LC279" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">if</span> ( gps.<span class="pl-smi">newData</span> ) {</td>
      </tr>
      <tr>
        <td id="L280" class="blob-num js-line-number" data-line-number="280"></td>
        <td id="LC280" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> ==================  GPS Update  ===================</span></td>
      </tr>
      <tr>
        <td id="L281" class="blob-num js-line-number" data-line-number="281"></td>
        <td id="LC281" class="blob-code blob-code-inner js-file-line">	gps.<span class="pl-smi">newData</span> = <span class="pl-c1">0</span>; <span class="pl-c"><span class="pl-c">//</span> Reset the flag</span></td>
      </tr>
      <tr>
        <td id="L282" class="blob-num js-line-number" data-line-number="282"></td>
        <td id="LC282" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L283" class="blob-num js-line-number" data-line-number="283"></td>
        <td id="LC283" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> Position, converted to NED</span></td>
      </tr>
      <tr>
        <td id="L284" class="blob-num js-line-number" data-line-number="284"></td>
        <td id="LC284" class="blob-code blob-code-inner js-file-line">	Vector3d <span class="pl-smi">pos_vec</span>(nav.<span class="pl-smi">lat</span>, nav.<span class="pl-smi">lon</span>, nav.<span class="pl-smi">alt</span>);</td>
      </tr>
      <tr>
        <td id="L285" class="blob-num js-line-number" data-line-number="285"></td>
        <td id="LC285" class="blob-code blob-code-inner js-file-line">	pos_ins_ecef = <span class="pl-c1">lla2ecef</span>(pos_vec);</td>
      </tr>
      <tr>
        <td id="L286" class="blob-num js-line-number" data-line-number="286"></td>
        <td id="LC286" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L287" class="blob-num js-line-number" data-line-number="287"></td>
        <td id="LC287" class="blob-code blob-code-inner js-file-line">	Vector3d pos_ref = pos_vec;</td>
      </tr>
      <tr>
        <td id="L288" class="blob-num js-line-number" data-line-number="288"></td>
        <td id="LC288" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">pos_ref</span>(<span class="pl-c1">2</span>) = <span class="pl-c1">0.0</span>;</td>
      </tr>
      <tr>
        <td id="L289" class="blob-num js-line-number" data-line-number="289"></td>
        <td id="LC289" class="blob-code blob-code-inner js-file-line">	pos_ins_ned = <span class="pl-c1">ecef2ned</span>(pos_ins_ecef, pos_ref);</td>
      </tr>
      <tr>
        <td id="L290" class="blob-num js-line-number" data-line-number="290"></td>
        <td id="LC290" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L291" class="blob-num js-line-number" data-line-number="291"></td>
        <td id="LC291" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">pos_gps</span>(<span class="pl-c1">0</span>) = gps.<span class="pl-smi">lat</span>*D2R;</td>
      </tr>
      <tr>
        <td id="L292" class="blob-num js-line-number" data-line-number="292"></td>
        <td id="LC292" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">pos_gps</span>(<span class="pl-c1">1</span>) = gps.<span class="pl-smi">lon</span>*D2R;</td>
      </tr>
      <tr>
        <td id="L293" class="blob-num js-line-number" data-line-number="293"></td>
        <td id="LC293" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">pos_gps</span>(<span class="pl-c1">2</span>) = gps.<span class="pl-smi">alt</span>;</td>
      </tr>
      <tr>
        <td id="L294" class="blob-num js-line-number" data-line-number="294"></td>
        <td id="LC294" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L295" class="blob-num js-line-number" data-line-number="295"></td>
        <td id="LC295" class="blob-code blob-code-inner js-file-line">	pos_gps_ecef = <span class="pl-c1">lla2ecef</span>(pos_gps);</td>
      </tr>
      <tr>
        <td id="L296" class="blob-num js-line-number" data-line-number="296"></td>
        <td id="LC296" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L297" class="blob-num js-line-number" data-line-number="297"></td>
        <td id="LC297" class="blob-code blob-code-inner js-file-line">	pos_gps_ned = <span class="pl-c1">ecef2ned</span>(pos_gps_ecef, pos_ref);</td>
      </tr>
      <tr>
        <td id="L298" class="blob-num js-line-number" data-line-number="298"></td>
        <td id="LC298" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L299" class="blob-num js-line-number" data-line-number="299"></td>
        <td id="LC299" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> Create Measurement: y</span></td>
      </tr>
      <tr>
        <td id="L300" class="blob-num js-line-number" data-line-number="300"></td>
        <td id="LC300" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">y</span>(<span class="pl-c1">0</span>) = <span class="pl-c1">pos_gps_ned</span>(<span class="pl-c1">0</span>) - <span class="pl-c1">pos_ins_ned</span>(<span class="pl-c1">0</span>);</td>
      </tr>
      <tr>
        <td id="L301" class="blob-num js-line-number" data-line-number="301"></td>
        <td id="LC301" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">y</span>(<span class="pl-c1">1</span>) = <span class="pl-c1">pos_gps_ned</span>(<span class="pl-c1">1</span>) - <span class="pl-c1">pos_ins_ned</span>(<span class="pl-c1">1</span>);</td>
      </tr>
      <tr>
        <td id="L302" class="blob-num js-line-number" data-line-number="302"></td>
        <td id="LC302" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">y</span>(<span class="pl-c1">2</span>) = <span class="pl-c1">pos_gps_ned</span>(<span class="pl-c1">2</span>) - <span class="pl-c1">pos_ins_ned</span>(<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L303" class="blob-num js-line-number" data-line-number="303"></td>
        <td id="LC303" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L304" class="blob-num js-line-number" data-line-number="304"></td>
        <td id="LC304" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">y</span>(<span class="pl-c1">3</span>) = gps.<span class="pl-smi">vn</span> - nav.<span class="pl-smi">vn</span>;</td>
      </tr>
      <tr>
        <td id="L305" class="blob-num js-line-number" data-line-number="305"></td>
        <td id="LC305" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">y</span>(<span class="pl-c1">4</span>) = gps.<span class="pl-smi">ve</span> - nav.<span class="pl-smi">ve</span>;</td>
      </tr>
      <tr>
        <td id="L306" class="blob-num js-line-number" data-line-number="306"></td>
        <td id="LC306" class="blob-code blob-code-inner js-file-line">	<span class="pl-c1">y</span>(<span class="pl-c1">5</span>) = gps.<span class="pl-smi">vd</span> - nav.<span class="pl-smi">vd</span>;</td>
      </tr>
      <tr>
        <td id="L307" class="blob-num js-line-number" data-line-number="307"></td>
        <td id="LC307" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L308" class="blob-num js-line-number" data-line-number="308"></td>
        <td id="LC308" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> Kalman Gain</span></td>
      </tr>
      <tr>
        <td id="L309" class="blob-num js-line-number" data-line-number="309"></td>
        <td id="LC309" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> K = P*H&#39;*inv(H*P*H&#39;+R)</span></td>
      </tr>
      <tr>
        <td id="L310" class="blob-num js-line-number" data-line-number="310"></td>
        <td id="LC310" class="blob-code blob-code-inner js-file-line">	K = P * H.<span class="pl-c1">transpose</span>() * (H * P * H.<span class="pl-c1">transpose</span>() + R).<span class="pl-c1">inverse</span>();</td>
      </tr>
      <tr>
        <td id="L311" class="blob-num js-line-number" data-line-number="311"></td>
        <td id="LC311" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L312" class="blob-num js-line-number" data-line-number="312"></td>
        <td id="LC312" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> Covariance Update</span></td>
      </tr>
      <tr>
        <td id="L313" class="blob-num js-line-number" data-line-number="313"></td>
        <td id="LC313" class="blob-code blob-code-inner js-file-line">	ImKH = I15 - K * H;	                <span class="pl-c"><span class="pl-c">//</span> ImKH = I - K*H</span></td>
      </tr>
      <tr>
        <td id="L314" class="blob-num js-line-number" data-line-number="314"></td>
        <td id="LC314" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L315" class="blob-num js-line-number" data-line-number="315"></td>
        <td id="LC315" class="blob-code blob-code-inner js-file-line">	KRKt = K * R * K.<span class="pl-c1">transpose</span>();		<span class="pl-c"><span class="pl-c">//</span> KRKt = K*R*K&#39;</span></td>
      </tr>
      <tr>
        <td id="L316" class="blob-num js-line-number" data-line-number="316"></td>
        <td id="LC316" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L317" class="blob-num js-line-number" data-line-number="317"></td>
        <td id="LC317" class="blob-code blob-code-inner js-file-line">	P = ImKH * P * ImKH.<span class="pl-c1">transpose</span>() + KRKt;	<span class="pl-c"><span class="pl-c">//</span> P = ImKH*P*ImKH&#39; + KRKt</span></td>
      </tr>
      <tr>
        <td id="L318" class="blob-num js-line-number" data-line-number="318"></td>
        <td id="LC318" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L319" class="blob-num js-line-number" data-line-number="319"></td>
        <td id="LC319" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">Pp0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">0</span>,<span class="pl-c1">0</span>);     nav.<span class="pl-smi">Pp1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">1</span>,<span class="pl-c1">1</span>);     nav.<span class="pl-smi">Pp2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">2</span>,<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L320" class="blob-num js-line-number" data-line-number="320"></td>
        <td id="LC320" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">Pv0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">3</span>,<span class="pl-c1">3</span>);     nav.<span class="pl-smi">Pv1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">4</span>,<span class="pl-c1">4</span>);     nav.<span class="pl-smi">Pv2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">5</span>,<span class="pl-c1">5</span>);</td>
      </tr>
      <tr>
        <td id="L321" class="blob-num js-line-number" data-line-number="321"></td>
        <td id="LC321" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">Pa0</span> = <span class="pl-c1">P</span>(<span class="pl-c1">6</span>,<span class="pl-c1">6</span>);     nav.<span class="pl-smi">Pa1</span> = <span class="pl-c1">P</span>(<span class="pl-c1">7</span>,<span class="pl-c1">7</span>);     nav.<span class="pl-smi">Pa2</span> = <span class="pl-c1">P</span>(<span class="pl-c1">8</span>,<span class="pl-c1">8</span>);</td>
      </tr>
      <tr>
        <td id="L322" class="blob-num js-line-number" data-line-number="322"></td>
        <td id="LC322" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">Pabx</span> = <span class="pl-c1">P</span>(<span class="pl-c1">9</span>,<span class="pl-c1">9</span>);    nav.<span class="pl-smi">Paby</span> = <span class="pl-c1">P</span>(<span class="pl-c1">10</span>,<span class="pl-c1">10</span>);  nav.<span class="pl-smi">Pabz</span> = <span class="pl-c1">P</span>(<span class="pl-c1">11</span>,<span class="pl-c1">11</span>);</td>
      </tr>
      <tr>
        <td id="L323" class="blob-num js-line-number" data-line-number="323"></td>
        <td id="LC323" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">Pgbx</span> = <span class="pl-c1">P</span>(<span class="pl-c1">12</span>,<span class="pl-c1">12</span>);  nav.<span class="pl-smi">Pgby</span> = <span class="pl-c1">P</span>(<span class="pl-c1">13</span>,<span class="pl-c1">13</span>);  nav.<span class="pl-smi">Pgbz</span> = <span class="pl-c1">P</span>(<span class="pl-c1">14</span>,<span class="pl-c1">14</span>);</td>
      </tr>
      <tr>
        <td id="L324" class="blob-num js-line-number" data-line-number="324"></td>
        <td id="LC324" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L325" class="blob-num js-line-number" data-line-number="325"></td>
        <td id="LC325" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> State Update</span></td>
      </tr>
      <tr>
        <td id="L326" class="blob-num js-line-number" data-line-number="326"></td>
        <td id="LC326" class="blob-code blob-code-inner js-file-line">	x = K * y;</td>
      </tr>
      <tr>
        <td id="L327" class="blob-num js-line-number" data-line-number="327"></td>
        <td id="LC327" class="blob-code blob-code-inner js-file-line">	denom = (<span class="pl-c1">1.0</span> - (ECC2 * <span class="pl-c1">sin</span>(nav.<span class="pl-smi">lat</span>) * <span class="pl-c1">sin</span>(nav.<span class="pl-smi">lat</span>)));</td>
      </tr>
      <tr>
        <td id="L328" class="blob-num js-line-number" data-line-number="328"></td>
        <td id="LC328" class="blob-code blob-code-inner js-file-line">	denom = <span class="pl-c1">sqrt</span>(denom*denom);</td>
      </tr>
      <tr>
        <td id="L329" class="blob-num js-line-number" data-line-number="329"></td>
        <td id="LC329" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L330" class="blob-num js-line-number" data-line-number="330"></td>
        <td id="LC330" class="blob-code blob-code-inner js-file-line">	Re = EARTH_RADIUS / <span class="pl-c1">sqrt</span>(denom);</td>
      </tr>
      <tr>
        <td id="L331" class="blob-num js-line-number" data-line-number="331"></td>
        <td id="LC331" class="blob-code blob-code-inner js-file-line">	Rn = EARTH_RADIUS * (<span class="pl-c1">1</span>-ECC2) / denom*<span class="pl-c1">sqrt</span>(denom);</td>
      </tr>
      <tr>
        <td id="L332" class="blob-num js-line-number" data-line-number="332"></td>
        <td id="LC332" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">alt</span> = nav.<span class="pl-smi">alt</span> - <span class="pl-c1">x</span>(<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L333" class="blob-num js-line-number" data-line-number="333"></td>
        <td id="LC333" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">lat</span> = nav.<span class="pl-smi">lat</span> + <span class="pl-c1">x</span>(<span class="pl-c1">0</span>)/(Re + nav.<span class="pl-smi">alt</span>);</td>
      </tr>
      <tr>
        <td id="L334" class="blob-num js-line-number" data-line-number="334"></td>
        <td id="LC334" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">lon</span> = nav.<span class="pl-smi">lon</span> + <span class="pl-c1">x</span>(<span class="pl-c1">1</span>)/(Rn + nav.<span class="pl-smi">alt</span>)/<span class="pl-c1">cos</span>(nav.<span class="pl-smi">lat</span>);</td>
      </tr>
      <tr>
        <td id="L335" class="blob-num js-line-number" data-line-number="335"></td>
        <td id="LC335" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L336" class="blob-num js-line-number" data-line-number="336"></td>
        <td id="LC336" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">vn</span> = nav.<span class="pl-smi">vn</span> + <span class="pl-c1">x</span>(<span class="pl-c1">3</span>);</td>
      </tr>
      <tr>
        <td id="L337" class="blob-num js-line-number" data-line-number="337"></td>
        <td id="LC337" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">ve</span> = nav.<span class="pl-smi">ve</span> + <span class="pl-c1">x</span>(<span class="pl-c1">4</span>);</td>
      </tr>
      <tr>
        <td id="L338" class="blob-num js-line-number" data-line-number="338"></td>
        <td id="LC338" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">vd</span> = nav.<span class="pl-smi">vd</span> + <span class="pl-c1">x</span>(<span class="pl-c1">5</span>);</td>
      </tr>
      <tr>
        <td id="L339" class="blob-num js-line-number" data-line-number="339"></td>
        <td id="LC339" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L340" class="blob-num js-line-number" data-line-number="340"></td>
        <td id="LC340" class="blob-code blob-code-inner js-file-line">	<span class="pl-c"><span class="pl-c">//</span> Attitude correction</span></td>
      </tr>
      <tr>
        <td id="L341" class="blob-num js-line-number" data-line-number="341"></td>
        <td id="LC341" class="blob-code blob-code-inner js-file-line">	dq = <span class="pl-c1">Quaterniond</span>(<span class="pl-c1">1.0</span>, <span class="pl-c1">x</span>(<span class="pl-c1">6</span>), <span class="pl-c1">x</span>(<span class="pl-c1">7</span>), <span class="pl-c1">x</span>(<span class="pl-c1">8</span>));</td>
      </tr>
      <tr>
        <td id="L342" class="blob-num js-line-number" data-line-number="342"></td>
        <td id="LC342" class="blob-code blob-code-inner js-file-line">	quat = (quat * dq).<span class="pl-c1">normalized</span>();</td>
      </tr>
      <tr>
        <td id="L343" class="blob-num js-line-number" data-line-number="343"></td>
        <td id="LC343" class="blob-code blob-code-inner js-file-line">		</td>
      </tr>
      <tr>
        <td id="L344" class="blob-num js-line-number" data-line-number="344"></td>
        <td id="LC344" class="blob-code blob-code-inner js-file-line">	Vector3d att_vec = <span class="pl-c1">quat2eul</span>(quat);</td>
      </tr>
      <tr>
        <td id="L345" class="blob-num js-line-number" data-line-number="345"></td>
        <td id="LC345" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">phi</span> = <span class="pl-c1">att_vec</span>(<span class="pl-c1">0</span>);</td>
      </tr>
      <tr>
        <td id="L346" class="blob-num js-line-number" data-line-number="346"></td>
        <td id="LC346" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">the</span> = <span class="pl-c1">att_vec</span>(<span class="pl-c1">1</span>);</td>
      </tr>
      <tr>
        <td id="L347" class="blob-num js-line-number" data-line-number="347"></td>
        <td id="LC347" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">psi</span> = <span class="pl-c1">att_vec</span>(<span class="pl-c1">2</span>);</td>
      </tr>
      <tr>
        <td id="L348" class="blob-num js-line-number" data-line-number="348"></td>
        <td id="LC348" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L349" class="blob-num js-line-number" data-line-number="349"></td>
        <td id="LC349" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">abx</span> += <span class="pl-c1">x</span>(<span class="pl-c1">9</span>);</td>
      </tr>
      <tr>
        <td id="L350" class="blob-num js-line-number" data-line-number="350"></td>
        <td id="LC350" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">aby</span> += <span class="pl-c1">x</span>(<span class="pl-c1">10</span>);</td>
      </tr>
      <tr>
        <td id="L351" class="blob-num js-line-number" data-line-number="351"></td>
        <td id="LC351" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">abz</span> += <span class="pl-c1">x</span>(<span class="pl-c1">11</span>);</td>
      </tr>
      <tr>
        <td id="L352" class="blob-num js-line-number" data-line-number="352"></td>
        <td id="LC352" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L353" class="blob-num js-line-number" data-line-number="353"></td>
        <td id="LC353" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">gbx</span> += <span class="pl-c1">x</span>(<span class="pl-c1">12</span>);</td>
      </tr>
      <tr>
        <td id="L354" class="blob-num js-line-number" data-line-number="354"></td>
        <td id="LC354" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">gby</span> += <span class="pl-c1">x</span>(<span class="pl-c1">13</span>);</td>
      </tr>
      <tr>
        <td id="L355" class="blob-num js-line-number" data-line-number="355"></td>
        <td id="LC355" class="blob-code blob-code-inner js-file-line">	nav.<span class="pl-smi">gbz</span> += <span class="pl-c1">x</span>(<span class="pl-c1">14</span>);</td>
      </tr>
      <tr>
        <td id="L356" class="blob-num js-line-number" data-line-number="356"></td>
        <td id="LC356" class="blob-code blob-code-inner js-file-line">    }</td>
      </tr>
      <tr>
        <td id="L357" class="blob-num js-line-number" data-line-number="357"></td>
        <td id="LC357" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L358" class="blob-num js-line-number" data-line-number="358"></td>
        <td id="LC358" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qw</span> = quat.<span class="pl-c1">w</span>();</td>
      </tr>
      <tr>
        <td id="L359" class="blob-num js-line-number" data-line-number="359"></td>
        <td id="LC359" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qx</span> = quat.<span class="pl-c1">x</span>();</td>
      </tr>
      <tr>
        <td id="L360" class="blob-num js-line-number" data-line-number="360"></td>
        <td id="LC360" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qy</span> = quat.<span class="pl-c1">y</span>();</td>
      </tr>
      <tr>
        <td id="L361" class="blob-num js-line-number" data-line-number="361"></td>
        <td id="LC361" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">qz</span> = quat.<span class="pl-c1">z</span>();</td>
      </tr>
      <tr>
        <td id="L362" class="blob-num js-line-number" data-line-number="362"></td>
        <td id="LC362" class="blob-code blob-code-inner js-file-line">	</td>
      </tr>
      <tr>
        <td id="L363" class="blob-num js-line-number" data-line-number="363"></td>
        <td id="LC363" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Remove current estimated biases from rate gyro and accels</span></td>
      </tr>
      <tr>
        <td id="L364" class="blob-num js-line-number" data-line-number="364"></td>
        <td id="LC364" class="blob-code blob-code-inner js-file-line">    imu.<span class="pl-smi">p</span> -= nav.<span class="pl-smi">gbx</span>;</td>
      </tr>
      <tr>
        <td id="L365" class="blob-num js-line-number" data-line-number="365"></td>
        <td id="LC365" class="blob-code blob-code-inner js-file-line">    imu.<span class="pl-smi">q</span> -= nav.<span class="pl-smi">gby</span>;</td>
      </tr>
      <tr>
        <td id="L366" class="blob-num js-line-number" data-line-number="366"></td>
        <td id="LC366" class="blob-code blob-code-inner js-file-line">    imu.<span class="pl-smi">r</span> -= nav.<span class="pl-smi">gbz</span>;</td>
      </tr>
      <tr>
        <td id="L367" class="blob-num js-line-number" data-line-number="367"></td>
        <td id="LC367" class="blob-code blob-code-inner js-file-line">    imu.<span class="pl-smi">ax</span> -= nav.<span class="pl-smi">abx</span>;</td>
      </tr>
      <tr>
        <td id="L368" class="blob-num js-line-number" data-line-number="368"></td>
        <td id="LC368" class="blob-code blob-code-inner js-file-line">    imu.<span class="pl-smi">ay</span> -= nav.<span class="pl-smi">aby</span>;</td>
      </tr>
      <tr>
        <td id="L369" class="blob-num js-line-number" data-line-number="369"></td>
        <td id="LC369" class="blob-code blob-code-inner js-file-line">    imu.<span class="pl-smi">az</span> -= nav.<span class="pl-smi">abz</span>;</td>
      </tr>
      <tr>
        <td id="L370" class="blob-num js-line-number" data-line-number="370"></td>
        <td id="LC370" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L371" class="blob-num js-line-number" data-line-number="371"></td>
        <td id="LC371" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> Get the new Specific forces and Rotation Rate,</span></td>
      </tr>
      <tr>
        <td id="L372" class="blob-num js-line-number" data-line-number="372"></td>
        <td id="LC372" class="blob-code blob-code-inner js-file-line">    <span class="pl-c"><span class="pl-c">//</span> use in the next time update</span></td>
      </tr>
      <tr>
        <td id="L373" class="blob-num js-line-number" data-line-number="373"></td>
        <td id="LC373" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">f_b</span>(<span class="pl-c1">0</span>) = imu.<span class="pl-smi">ax</span>;</td>
      </tr>
      <tr>
        <td id="L374" class="blob-num js-line-number" data-line-number="374"></td>
        <td id="LC374" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">f_b</span>(<span class="pl-c1">1</span>) = imu.<span class="pl-smi">ay</span>;</td>
      </tr>
      <tr>
        <td id="L375" class="blob-num js-line-number" data-line-number="375"></td>
        <td id="LC375" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">f_b</span>(<span class="pl-c1">2</span>) = imu.<span class="pl-smi">az</span>;</td>
      </tr>
      <tr>
        <td id="L376" class="blob-num js-line-number" data-line-number="376"></td>
        <td id="LC376" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L377" class="blob-num js-line-number" data-line-number="377"></td>
        <td id="LC377" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">om_ib</span>(<span class="pl-c1">0</span>) = imu.<span class="pl-smi">p</span>;</td>
      </tr>
      <tr>
        <td id="L378" class="blob-num js-line-number" data-line-number="378"></td>
        <td id="LC378" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">om_ib</span>(<span class="pl-c1">1</span>) = imu.<span class="pl-smi">q</span>;</td>
      </tr>
      <tr>
        <td id="L379" class="blob-num js-line-number" data-line-number="379"></td>
        <td id="LC379" class="blob-code blob-code-inner js-file-line">    <span class="pl-c1">om_ib</span>(<span class="pl-c1">2</span>) = imu.<span class="pl-smi">r</span>;</td>
      </tr>
      <tr>
        <td id="L380" class="blob-num js-line-number" data-line-number="380"></td>
        <td id="LC380" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L381" class="blob-num js-line-number" data-line-number="381"></td>
        <td id="LC381" class="blob-code blob-code-inner js-file-line">    nav.<span class="pl-smi">time</span> = imu.<span class="pl-smi">time</span>;</td>
      </tr>
      <tr>
        <td id="L382" class="blob-num js-line-number" data-line-number="382"></td>
        <td id="LC382" class="blob-code blob-code-inner js-file-line">    </td>
      </tr>
      <tr>
        <td id="L383" class="blob-num js-line-number" data-line-number="383"></td>
        <td id="LC383" class="blob-code blob-code-inner js-file-line">    <span class="pl-k">return</span> nav;</td>
      </tr>
      <tr>
        <td id="L384" class="blob-num js-line-number" data-line-number="384"></td>
        <td id="LC384" class="blob-code blob-code-inner js-file-line">}</td>
      </tr>
      <tr>
        <td id="L385" class="blob-num js-line-number" data-line-number="385"></td>
        <td id="LC385" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L386" class="blob-num js-line-number" data-line-number="386"></td>
        <td id="LC386" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L387" class="blob-num js-line-number" data-line-number="387"></td>
        <td id="LC387" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">ifdef</span> HAVE_BOOST_PYTHON</td>
      </tr>
      <tr>
        <td id="L388" class="blob-num js-line-number" data-line-number="388"></td>
        <td id="LC388" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L389" class="blob-num js-line-number" data-line-number="389"></td>
        <td id="LC389" class="blob-code blob-code-inner js-file-line"><span class="pl-c"><span class="pl-c">//</span> The following constructs a python interface for this class.</span></td>
      </tr>
      <tr>
        <td id="L390" class="blob-num js-line-number" data-line-number="390"></td>
        <td id="LC390" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L391" class="blob-num js-line-number" data-line-number="391"></td>
        <td id="LC391" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/python.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L392" class="blob-num js-line-number" data-line-number="392"></td>
        <td id="LC392" class="blob-code blob-code-inner js-file-line"><span class="pl-k">using</span> <span class="pl-k">namespace</span> <span class="pl-en">boost</span>::python<span class="pl-k">;</span></td>
      </tr>
      <tr>
        <td id="L393" class="blob-num js-line-number" data-line-number="393"></td>
        <td id="LC393" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L394" class="blob-num js-line-number" data-line-number="394"></td>
        <td id="LC394" class="blob-code blob-code-inner js-file-line"><span class="pl-en">BOOST_PYTHON_MODULE</span>(EKF15)</td>
      </tr>
      <tr>
        <td id="L395" class="blob-num js-line-number" data-line-number="395"></td>
        <td id="LC395" class="blob-code blob-code-inner js-file-line">{</td>
      </tr>
      <tr>
        <td id="L396" class="blob-num js-line-number" data-line-number="396"></td>
        <td id="LC396" class="blob-code blob-code-inner js-file-line">    class_&lt;EKF15&gt;(<span class="pl-s"><span class="pl-pds">&quot;</span>EKF15<span class="pl-pds">&quot;</span></span>)</td>
      </tr>
      <tr>
        <td id="L397" class="blob-num js-line-number" data-line-number="397"></td>
        <td id="LC397" class="blob-code blob-code-inner js-file-line">        .<span class="pl-c1">def</span>(<span class="pl-s"><span class="pl-pds">&quot;</span>set_config<span class="pl-pds">&quot;</span></span>, &amp;EKF15::set_config)</td>
      </tr>
      <tr>
        <td id="L398" class="blob-num js-line-number" data-line-number="398"></td>
        <td id="LC398" class="blob-code blob-code-inner js-file-line">        .<span class="pl-c1">def</span>(<span class="pl-s"><span class="pl-pds">&quot;</span>init<span class="pl-pds">&quot;</span></span>, &amp;EKF15::init)</td>
      </tr>
      <tr>
        <td id="L399" class="blob-num js-line-number" data-line-number="399"></td>
        <td id="LC399" class="blob-code blob-code-inner js-file-line">        .<span class="pl-c1">def</span>(<span class="pl-s"><span class="pl-pds">&quot;</span>update<span class="pl-pds">&quot;</span></span>, &amp;EKF15::update)</td>
      </tr>
      <tr>
        <td id="L400" class="blob-num js-line-number" data-line-number="400"></td>
        <td id="LC400" class="blob-code blob-code-inner js-file-line">    ;</td>
      </tr>
      <tr>
        <td id="L401" class="blob-num js-line-number" data-line-number="401"></td>
        <td id="LC401" class="blob-code blob-code-inner js-file-line">}</td>
      </tr>
      <tr>
        <td id="L402" class="blob-num js-line-number" data-line-number="402"></td>
        <td id="LC402" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L403" class="blob-num js-line-number" data-line-number="403"></td>
        <td id="LC403" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">endif</span> <span class="pl-c"><span class="pl-c">//</span> HAVE_BOOST_PYTHON</span></td>
      </tr>
</table>


  </div>

  </div>

  <button type="button" data-facebox="#jump-to-line" data-facebox-class="linejump" data-hotkey="l" class="d-none">Jump to Line</button>
  <div id="jump-to-line" style="display:none">
    <!-- '"` --><!-- </textarea></xmp> --></option></form><form accept-charset="UTF-8" action="" class="js-jump-to-line-form" method="get"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /></div>
      <input class="form-control linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" aria-label="Jump to line" autofocus>
      <button type="submit" class="btn">Go</button>
</form>  </div>

  </div>
  <div class="modal-backdrop js-touch-events"></div>
</div>

    </div>
  </div>

  </div>

      
<div class="container site-footer-container">
  <div class="site-footer " role="contentinfo">
    <ul class="site-footer-links float-right">
        <li><a href="https://github.com/contact" data-ga-click="Footer, go to contact, text:contact">Contact GitHub</a></li>
      <li><a href="https://developer.github.com" data-ga-click="Footer, go to api, text:api">API</a></li>
      <li><a href="https://training.github.com" data-ga-click="Footer, go to training, text:training">Training</a></li>
      <li><a href="https://shop.github.com" data-ga-click="Footer, go to shop, text:shop">Shop</a></li>
        <li><a href="https://github.com/blog" data-ga-click="Footer, go to blog, text:blog">Blog</a></li>
        <li><a href="https://github.com/about" data-ga-click="Footer, go to about, text:about">About</a></li>

    </ul>

    <a href="https://github.com" aria-label="Homepage" class="site-footer-mark" title="GitHub">
      <svg aria-hidden="true" class="octicon octicon-mark-github" height="24" version="1.1" viewBox="0 0 16 16" width="24"><path fill-rule="evenodd" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0 0 16 8c0-4.42-3.58-8-8-8z"/></svg>
</a>
    <ul class="site-footer-links">
      <li>&copy; 2017 <span title="0.18580s from unicorn-1586187012-qpvgn">GitHub</span>, Inc.</li>
        <li><a href="https://github.com/site/terms" data-ga-click="Footer, go to terms, text:terms">Terms</a></li>
        <li><a href="https://github.com/site/privacy" data-ga-click="Footer, go to privacy, text:privacy">Privacy</a></li>
        <li><a href="https://github.com/security" data-ga-click="Footer, go to security, text:security">Security</a></li>
        <li><a href="https://status.github.com/" data-ga-click="Footer, go to status, text:status">Status</a></li>
        <li><a href="https://help.github.com" data-ga-click="Footer, go to help, text:help">Help</a></li>
    </ul>
  </div>
</div>



  <div id="ajax-error-message" class="ajax-error-message flash flash-error">
    <svg aria-hidden="true" class="octicon octicon-alert" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M8.865 1.52c-.18-.31-.51-.5-.87-.5s-.69.19-.87.5L.275 13.5c-.18.31-.18.69 0 1 .19.31.52.5.87.5h13.7c.36 0 .69-.19.86-.5.17-.31.18-.69.01-1L8.865 1.52zM8.995 13h-2v-2h2v2zm0-3h-2V6h2v4z"/></svg>
    <button type="button" class="flash-close js-flash-close js-ajax-error-dismiss" aria-label="Dismiss error">
      <svg aria-hidden="true" class="octicon octicon-x" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M7.48 8l3.75 3.75-1.48 1.48L6 9.48l-3.75 3.75-1.48-1.48L4.52 8 .77 4.25l1.48-1.48L6 6.52l3.75-3.75 1.48 1.48z"/></svg>
    </button>
    You can't perform that action at this time.
  </div>


    
    <script crossorigin="anonymous" integrity="sha256-+Eu4exSWhdHmxvBX7jJPLNSW5nf1o1motduFMxO7g+Y=" src="https://assets-cdn.github.com/assets/frameworks-f84bb87b149685d1e6c6f057ee324f2cd496e677f5a359a8b5db853313bb83e6.js"></script>
    
    <script async="async" crossorigin="anonymous" integrity="sha256-ShUbbPU8svmGOF51j4uI9EeR0yHsGSP0DwV2nhQZ7fQ=" src="https://assets-cdn.github.com/assets/github-4a151b6cf53cb2f986385e758f8b88f44791d321ec1923f40f05769e1419edf4.js"></script>
    
    
    
    
  <div class="js-stale-session-flash stale-session-flash flash flash-warn flash-banner d-none">
    <svg aria-hidden="true" class="octicon octicon-alert" height="16" version="1.1" viewBox="0 0 16 16" width="16"><path fill-rule="evenodd" d="M8.865 1.52c-.18-.31-.51-.5-.87-.5s-.69.19-.87.5L.275 13.5c-.18.31-.18.69 0 1 .19.31.52.5.87.5h13.7c.36 0 .69-.19.86-.5.17-.31.18-.69.01-1L8.865 1.52zM8.995 13h-2v-2h2v2zm0-3h-2V6h2v4z"/></svg>
    <span class="signed-in-tab-flash">You signed in with another tab or window. <a href="">Reload</a> to refresh your session.</span>
    <span class="signed-out-tab-flash">You signed out in another tab or window. <a href="">Reload</a> to refresh your session.</span>
  </div>
  <div class="facebox" id="facebox" style="display:none;">
  <div class="facebox-popup">
    <div class="facebox-content" role="dialog" aria-labelledby="facebox-header" aria-describedby="facebox-description">
    </div>
    <button type="button" class="facebox-close js-facebox-close" aria-label="Close modal">
      <svg aria-hidden="true" class="octicon octicon-x" height="16" version="1.1" viewBox="0 0 12 16" width="12"><path fill-rule="evenodd" d="M7.48 8l3.75 3.75-1.48 1.48L6 9.48l-3.75 3.75-1.48-1.48L4.52 8 .77 4.25l1.48-1.48L6 6.52l3.75-3.75 1.48 1.48z"/></svg>
    </button>
  </div>
</div>


  </body>
</html>

