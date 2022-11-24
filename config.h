/* See LICENSE file for copyright and license details. */

//source for multimedia key stuff (light -- I haven't implemented): https://gist.github.com/palopezv/efd34059af6126ad970940bcc6a90f2e


/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
       					"monospace:pixelsize=20",
				       	"fontawesome:pixelsize=18"
					"ttf-joypixels:pixelsize=16",
					"noto-font-emoji:pixelsize=16",
				      };
static const char dmenufont[]       = "monospace:pixelsize=20";
static const char col_gray1[]       = "#C31313";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#Ea0909";

static const char col_charcoal[]    = "#28231D";
static const char col_lpurple[]     = "#C3AAF5";
static const char col_mintgreen[]   = "#8FC9A3";
static const char col_butter[]      = "#f7df75";
static const char col_dyellow[]     = "#8B8000";
static const char col_gold[]        = "#FFD700";
static const char col_goldyellow[]  = "#FFC000";
static const char col_white[]       = "#ffffff";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white , col_charcoal, col_charcoal },
	[SchemeSel]  = { col_white , col_gray1,  col_gold },
};



/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 4,       1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "obs",      NULL, 	  NULL,       1 << 7,       0,           -1 },
	{ "Audacity", NULL,   	  NULL,       1 << 6,       0,           -1 },
	{ "Pcmanfm",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Signal",   NULL,       NULL,       1 << 5,       0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Brave",    NULL,       NULL,       1 << 2,       0,           -1 },
	{ "surf",     NULL,       NULL,       1 << 2,       0,           -1 },
	{ "code",     NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#include "shiftview.c"
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "5", "-g", "5", "-m", dmenumon, "-fn", dmenufont, "-nb", col_charcoal, "-nf", col_white , "-sb", col_gray1 , "-sf", col_white , NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *alt_termcmd[] = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,		                    XK_Print,  spawn,          SHCMD("~/scripts/screenshot") },               //Screenshot keybind
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("systemctl suspend") },                  //put machine to sleep
	{ MODKEY|ShiftMask,             XK_k,      spawn,          SHCMD("shutdown now") },                       //shutdown keybind
	{ Mod1Mask|ShiftMask,	        XK_d,      spawn,          {.v = dmenucmd } },                            //Runlauncher (dmenu) keybind

				    	//program launch keybinds
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("brave") },                              //Launch Brave
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("firefox") },                            //Launch Firefox
	{ MODKEY|ShiftMask, 		    XK_d,	   spawn,	       SHCMD("discord")},				              //Launch Discord
	{ Mod1Mask|ShiftMask,           XK_Return, spawn,          {.v = termcmd } },                             //Launch Terminal (kitty)
	{ Mod1Mask,			            XK_Return, spawn,	       {.v = alt_termcmd } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("flatpak run org.kde.kdenlive") },       //Launch Kdenlive
	{ MODKEY,			            XK_o,      spawn,          SHCMD("flatpak run com.obsproject.Studio")},   //Launch OBS
	{ Mod1Mask|ShiftMask,   		XK_s, 	   spawn, 	       SHCMD("flatpak run com.valvesoftware.Steam")}, //Launch Steam
	{ MODKEY|ShiftMask,	        	XK_p,	   spawn,	       SHCMD("pcmanfm")}, 			            	  //Launch Pcmanfm
    { MODKEY,                       XK_b,      spawn,          SHCMD("blueman-manager") },                    //bluetooth manager

	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },                                         //Hide/Show status bar
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },                                  //Switch Focused Window clockwise
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },                                  //Switch Focused Window counter-clockwise
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },                                  //change layout
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },                                  //change layout
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },                                //increase size of main window
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },                                //decrease size of main window
	{ MODKEY,                       XK_Return, zoom,           {0} },                                         //move focused window to master position
	{ MODKEY,                       XK_Tab,    view,           {0} },                                         
	{ Mod1Mask|ShiftMask,		    XK_c,      killclient,     {0} },                                         //kills focused window                                            
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },                                 //Switch Focused Monitor left
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },                                 //Switch Focused Monitor right
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },				 //Move Focused Window to Monitor Left
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },				 //Move Focused Window to Monitor Right
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },                                 //Decrease gap size
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },                                 //Increase gap size
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },                                 //Set gap size to 0
	{ Mod1Mask,            		    XK_Tab,    shiftview,      { .i = +1 } },                                //Switch to next tag
	{ Mod1Mask|ShiftMask,   	    XK_Tab,    shiftview,      { .i = -1 } },                                //Switch to prev tag
    { 0,                       XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer -d 5") },
	{ 0,                       XF86XK_AudioMute, spawn, SHCMD("pamixer -t") },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer -i 5")},

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_F4,     quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

