//----------------------------------------------------------------------------------------------------------------------
// 44 SVG icons (source www.iconset.io) + access methods
// (w) 2025 Jan Buchholz
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <map>
#include <optional>
#include <ranges>
#include <wx/wx.h>

static constexpr char svg_file_new[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M220-80q-24 0-42-18t-18-42v-680q0-24 18-42t42-18h361l219 219v521q0 24-18 42t-42
    18H220Zm331-554v-186H220v680h520v-494H551ZM220-820v186-186 680-680Z"/></svg>
    )SVG";
static constexpr char svg_file_open[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M140-160q-23 0-41.5-18.5T80-220v-520q0-23 18.5-41.5T140-800h281l60 60h339q23 0
    41.5 18.5T880-680H455l-60-60H140v520l102-400h698L833-206q-6 24-22 35t-41
    11H140Zm63-60h572l84-340H287l-84 340Zm0 0 84-340-84 340Zm-63-460v-60 60Z"/></svg>
    )SVG";
static constexpr char svg_file_save[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M840-683v503q0 24-18 42t-42 18H180q-24 0-42-18t-18-42v-600q0-24 18-42t42-18h503l157
    157Zm-60 27L656-780H180v600h600v-476ZM479.765-245Q523-245 553.5-275.265q30.5-30.264
    30.5-73.5Q584-392 553.735-422.5q-30.264-30.5-73.5-30.5Q437-453 406.5-422.735q-30.5 30.264-30.5
    73.5Q376-306 406.265-275.5q30.264 30.5 73.5 30.5ZM233-584h358v-143H233v143Zm-53-72v476-600
    124Z"/></svg>
    )SVG";
static constexpr char svg_file_save_as[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M180-120q-24.75 0-42.375-17.625T120-180v-600q0-24.75 17.625-42.375T180-840h503l157
    157v258l-60 60v-291L656-780H180v600h416l-60 60H180Zm299.765-125Q523-245 553.5-275.265q30.5-30.264
    30.5-73.5Q584-392 553.735-422.5q-30.264-30.5-73.5-30.5Q437-453 406.5-422.735q-30.5 30.264-30.5
    73.5Q376-306 406.265-275.5q30.264 30.5 73.5 30.5ZM233-584h358v-143H233v143ZM590-40v-50l228-228
    50 50L640-40h-50Zm304-254-50-50 39-39q6-6 10.5-6t10.5 6l27 27q6 6 6 12.5t-6 12.5l-37
    37ZM180-180v-600 600Z"/></svg>
    )SVG";
static constexpr char svg_file_quit[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M440-450q13 0 21.5-9t8.5-21q0-13-8.5-21.5T440-510q-12 0-21 8.5t-9 21.5q0 12 9 21t21
    9ZM260-120v-60l280-49v-466q0-14-7.5-24.5T512-732l-252-39v-59l266 46q32 5 53 30.5t21 57.5v516l-340
    60Zm-140 0v-60h80v-590q0-26 17.5-43t42.5-17h440q26 0 43 17t17
    43v590h80v60H120Zm140-60h440v-590l-440-1v591Z"/></svg>
    )SVG";
static constexpr char svg_file_quit_2[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M479.825-478Q467-478 458.5-486.625T450-508v-346q0-12.75 8.675-21.375 8.676-8.625
    21.5-8.625 12.825 0 21.325 8.625T510-854v346q0 12.75-8.675 21.375-8.676 8.625-21.5
    8.625ZM480-118q-75 0-140.5-28.5t-114-77q-48.5-48.5-77-114T120-478q0-64 22.5-123.5T207-709q9-10
    22-10.5t22.75 9.25Q260-702 258.5-689.5T249-667q-34 39-51.5 88.237Q180-529.527 180-478q0 125.357
    87.321 212.679Q354.643-178 480-178t212.679-87.321Q780-352.643
    780-478q0-53-17.5-101.5T711-668q-8.333-10.045-9.167-22.023Q701-702 709-710q10-10 24-9t23
    12q42 48 63 107t21 122q0 75-28.5 140.5t-77 114q-48.5 48.5-114 77T480-118Z"/></svg>
    )SVG";
static constexpr char svg_edit_copy[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M180-81q-24 0-42-18t-18-42v-603h60v603h474v60H180Zm120-120q-24 0-42-18t-18-42v-560q0-24
    18-42t42-18h440q24 0 42 18t18 42v560q0 24-18 42t-42 18H300Zm0-60h440v-560H300v560Zm0 0v-560
    560Z"/></svg>
    )SVG";
static constexpr char svg_edit_cut[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M782-114 481-415 364-298q11 17 13.5 33t2.5 35q0 64-43 107T230-80q-64
    0-107-43T80-230q0-64 43-107t107-43q18 0 35.5 5t36.5 15l116-116-118-118q-17 8-34.5 11t-35.5
    3q-64 0-107-43T80-730q0-64 43-107t107-43q64 0 107 43t43 107q0 19-2.5 36T367-662l514
    514v34h-99ZM599-527l-66-66 249-249h99v33L599-527ZM230-640q38 0 64-26t26-64q0-38-26-64t-64-26q-38
    0-64 26t-26 64q0 38 26 64t64 26Zm253 183q8 0 13.5-5.5T502-476q0-8-5.5-13.5T483-495q-8
    0-13.5 5.5T464-476q0 8 5.5 13.5T483-457ZM230-140q38 0 64-26t26-64q0-38-26-64t-64-26q-38 0-64
    26t-26 64q0 38 26 64t64 26Z"/></svg>
    )SVG";
static constexpr char svg_edit_paste[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M180-120q-26 0-43-17t-17-43v-600q0-26 17-43t43-17h202q7-35 34.5-57.5T480-920q36 0
    63.5 22.5T578-840h202q26 0 43 17t17 43v600q0 26-17 43t-43
    17H180Zm0-60h600v-600h-60v90H240v-90h-60v600Zm300-600q17 0
    28.5-11.5T520-820q0-17-11.5-28.5T480-860q-17 0-28.5 11.5T440-820q0 17 11.5 28.5T480-780Z"/></svg>
    )SVG";
static constexpr char svg_edit_select_all[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M240-240v-480h480v480H240Zm60-60h360v-360H300v360ZM180-120q-24
    0-42-18t-18-42h60v60Zm-60-660q0-24 18-42t42-18v60h-60Zm120
    660v-60h125v60H240Zm0-660v-60h125v60H240Zm185 660v-60h110v60H425Zm0-660v-60h110v60H425Zm170
    660v-60h125v60H595Zm0-660v-60h125v60H595Zm185 660v-60h60q0 24-18 42t-42 18Zm0-660v-60q24 0 42
    18t18 42h-60ZM120-240v-125h60v125h-60Zm0-185v-111h60v111h-60Zm0-171v-124h60v124h-60Zm660
    356v-125h60v125h-60Zm0-185v-111h60v111h-60Zm0-171v-124h60v124h-60Z"/></svg>
    )SVG";
static constexpr char svg_edit_undo[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M259-200v-60h310q70 0 120.5-46.5T740-422q0-69-50.5-115.5T569-584H274l114 114-42
    42-186-186 186-186 42 42-114 114h294q95 0 163.5 64T800-422q0 94-68.5 158T568-200H259Z"/></svg>
    )SVG";
static constexpr char svg_edit_redo[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M392-200q-95 0-163.5-64T160-422q0-94 68.5-158T392-644h294L572-758l42-42 186
    186-186 186-42-42 114-114H391q-70 0-120.5 46.5T220-422q0 69 50.5
    115.5T391-260h310v60H392Z"/></svg>
    )SVG";
static constexpr char svg_help_info[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M453-280h60v-240h-60v240Zm26.982-314q14.018 0
    23.518-9.2T513-626q0-14.45-9.482-24.225-9.483-9.775-23.5-9.775-14.018 0-23.518
    9.775T447-626q0 13.6 9.482 22.8 9.483 9.2 23.5 9.2Zm.284 514q-82.734
    0-155.5-31.5t-127.266-86q-54.5-54.5-86-127.341Q80-397.681 80-480.5q0-82.819
    31.5-155.659Q143-709 197.5-763t127.341-85.5Q397.681-880 480.5-880q82.819 0 155.659
    31.5Q709-817 763-763t85.5 127Q880-563 880-480.266q0 82.734-31.5
    155.5T763-197.684q-54 54.316-127 86Q563-80 480.266-80Zm.234-60Q622-140
    721-239.5t99-241Q820-622 721.188-721 622.375-820 480-820q-141 0-240.5
    98.812Q140-622.375 140-480q0 141 99.5 240.5t241 99.5Zm-.5-340Z"/></svg>
    )SVG";
static constexpr char svg_misc_font[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M264-240h67l45-124h209l45 124h66L512-720h-65L264-240Zm133-179 82-230h2l82
    230H397ZM140-80q-24 0-42-18t-18-42v-680q0-24 18-42t42-18h680q24 0 42 18t18 42v680q0 24-18
    42t-42 18H140Zm1-60h680v-680H141v680Zm0-680v680-680Z"/></svg>
    )SVG";
static constexpr char svg_misc_locked[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M220-80q-24.75 0-42.375-17.625T160-140v-434q0-24.75
    17.625-42.375T220-634h70v-96q0-78.85 55.606-134.425Q401.212-920
    480.106-920T614.5-864.425Q670-808.85 670-730v96h70q24.75 0 42.375 17.625T800-574v434q0
    24.75-17.625 42.375T740-80H220Zm0-60h520v-434H220v434Zm260.168-140Q512-280
    534.5-302.031T557-355q0-30-22.668-54.5t-54.5-24.5Q448-434 425.5-409.5t-22.5 55q0 30.5
    22.668 52.5t54.5 22ZM350-634h260v-96q0-54.167-37.882-92.083-37.883-37.917-92-37.917Q426-860
    388-822.083 350-784.167 350-730v96ZM220-140v-434 434Z"/></svg>
    )SVG";
static constexpr char svg_misc_unlocked[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M220-140h520v-434H220v434Zm260.168-140Q512-280
    534.5-302.031T557-355q0-30-22.668-54.5t-54.5-24.5Q448-434 425.5-409.5t-22.5 55q0 30.5
    22.668 52.5t54.5 22ZM220-140v-434 434Zm0 60q-24.75 0-42.375-17.625T160-140v-434q0-24.75
    17.625-42.375T220-634h330v-96q0-78.85 55.606-134.425Q661.212-920
    740.106-920T874.5-864.425Q930-808.85 930-730h-60q0-54-37.882-92-37.883-38-92-38Q686-860
    648-822.083 610-784.167 610-730v96h130q24.75 0 42.375 17.625T800-574v434q0 24.75-17.625
    42.375T740-80H220Z"/></svg>
    )SVG";
static constexpr char svg_misc_key[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M280-412q-28 0-48-20t-20-48q0-28 20-48t48-20q28 0 48 20t20 48q0 28-20 48t-48 20Zm0
    172q-100 0-170-70T40-480q0-100 70-170t170-70q72 0 126 34t85 103h356l113 113-167 153-88-64-88
    64-75-60h-51q-25 60-78.5 98.5T280-240Zm0-60q58 0 107-38.5t63-98.5h114l54 45 88-63 82 62
    85-79-51-51H450q-12-56-60-96.5T280-660q-75 0-127.5 52.5T100-480q0 75 52.5
    127.5T280-300Z"/></svg>
    )SVG";
static constexpr char svg_misc_settings[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="m388-80-20-126q-19-7-40-19t-37-25l-118 54-93-164 108-79q-2-9-2.5-20.5T185-480q0-9
    .5-20.5T188-521L80-600l93-164 118 54q16-13 37-25t40-18l20-127h184l20 126q19 7
    40.5 18.5T669-710l118-54 93 164-108 77q2 10 2.5 21.5t.5 21.5q0 10-.5 21t-2.5 21l108
    78-93 164-118-54q-16 13-36.5 25.5T592-206L572-80H388Zm92-270q54 0
    92-38t38-92q0-54-38-92t-92-38q-54 0-92 38t-38 92q0 54 38 92t92 38Zm0-60q-29
    0-49.5-20.5T410-480q0-29 20.5-49.5T480-550q29 0 49.5 20.5T550-480q0 29-20.5
    49.5T480-410Zm0-70Zm-44 340h88l14-112q33-8 62.5-25t53.5-41l106 46 40-72-94-69q4-17
    6.5-33.5T715-480q0-17-2-33.5t-7-33.5l94-69-40-72-106 46q-23-26-52-43.5T538-708l-14-112h-88l-14
    112q-34 7-63.5 24T306-642l-106-46-40 72 94 69q-4 17-6.5 33.5T245-480q0 17 2.5 33.5T254-413l-94
    69 40 72 106-46q24 24 53.5 41t62.5 25l14 112Z"/></svg>
    )SVG";
static constexpr char svg_misc_item_add[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M450-234h60v-129h130v-60H510v-130h-60v130H320v60h130v129ZM220-80q-24
    0-42-18t-18-42v-680q0-24 18-42t42-18h361l219 219v521q0 24-18 42t-42
    18H220Zm331-554v-186H220v680h520v-494H551ZM220-820v186-186 680-680Z"/></svg>
    )SVG";
static constexpr char svg_misc_item_edit[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M480-120v-71l216-216 71 71-216 216h-71ZM120-330v-60h300v60H120Zm690-49-71-71
    29-29q8-8 21-8t21 8l29 29q8 8 8 21t-8 21l-29
    29ZM120-495v-60h470v60H120Zm0-165v-60h470v60H120Z"/></svg>
    )SVG";
static constexpr char svg_misc_item_edit_2[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M180-12q-24 0-42-18t-18-42v-600q0-24 18-42t42-18h405l-60 60H180v600h600v-348l60-60v408q0
    24-18 42t-42 18H180Zm300-360Zm182-352 43 42-285 284v86h85l286-286 42 42-303
    304H360v-170l302-302Zm171 168L662-724l100-100q17-17 42.311-17T847-823l84 85q17 18 17
    42.472T930-654l-97 98Z"/></svg>
    )SVG";
static constexpr char svg_misc_item_delete[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M261-120q-24.75 0-42.375-17.625T201-180v-570h-41v-60h188v-30h264v30h188v60h-41v570q0
    24-18 42t-42 18H261Zm438-630H261v570h438v-570ZM367-266h60v-399h-60v399Zm166
    0h60v-399h-60v399ZM261-750v570-570Z"/></svg>
    )SVG";
static constexpr char svg_misc_create_folder[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M550-320h60v-90h90v-60h-90v-90h-60v90h-90v60h90v90ZM140-160q-24
    0-42-18.5T80-220v-520q0-23 18-41.5t42-18.5h281l60 60h339q23 0 41.5 18.5T880-680v460q0 23-18.5
    41.5T820-160H140Zm0-60h680v-460H456l-60-60H140v520Zm0 0v-520 520Z"/></svg>
    )SVG";
static constexpr char svg_misc_expand[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M480-80 240-320l44-44 196 196 196-196 44 44L480-80ZM284-596l-44-44 240-240 240
    240-44 44-196-196-196 196Z"/></svg>
    )SVG";
static constexpr char svg_misc_collapse[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="m290-85-42-42 232-232 232 232-42 42-190-190L290-85Zm190-517L248-834l42-42 190 190
    190-190 42 42-232 232Z"/></svg>
    )SVG";
static constexpr char svg_misc_check[] = R"SVG(<svg xmlns="http://www.w3.org/2000/svg" width="48" 
    height="48" viewBox="0 -960 960 960"><path d="M378-246 154-470l43-43 181 181 384-384 43 43-427 
    427Z"/></svg>
    )SVG";    
static constexpr char svc_misc_up[] = R"SVG(<svg xmlns="http://www.w3.org/2000/svg" width="48" 
    height="48" viewBox="0 -960 960 960"><path d="M450-160v-526L202-438l-42-42 320-320 320 
    320-42 42-248-248v526h-60Z"/></svg>
    )SVG";
static constexpr char svc_misc_down[] = R"SVG(<svg xmlns="http://www.w3.org/2000/svg" width="48" 
    height="48" viewBox="0 -960 960 960"><path d="M450-800v526L202-522l-42 42 320 320 
    320-320-42-42-248 248v-526h-60Z"/></svg>
    )SVG"; 
static constexpr char svg_misc_build[] = R"SVG(<svg xmlns="http://www.w3.org/2000/svg" width="48" 
    height="48" viewBox="0 -960 960 960"><path d="m643-273 44-41q7-7 7-15.5t-7-15.5L535-497q5-14 
    8-27t3-27q0-58-41-99t-99-41q-17 0-34 5t-33 14l88 87-54 51-86-85q-9 16-13.5 33t-4.5 35q0 57 40 
    96.5t97 39.5q14 0 27.5-2.5T461-425l151 152q6 6 15.5 6t15.5-6ZM480-80q-82 
    0-155-31.5t-127.5-86Q143-252 111.5-325T80-480q0-83 31.5-156t86-127Q252-817 
    325-848.5T480-880q83 0 156 31.5T763-763q54 54 85.5 127T880-480q0 82-31.5 
    155T763-197.5q-54 54.5-127 86T480-80Zm0-60q142 0 241-99.5T820-480q0-142-99-241t-241-99q-141 
    0-240.5 99T140-480q0 141 99.5 240.5T480-140Zm0-340Z"/></svg>
    )SVG";       
static constexpr char svg_art_article[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M277-279h275v-60H277v60Zm0-171h406v-60H277v60Zm0-171h406v-60H277v60Zm-97
    501q-24 0-42-18t-18-42v-600q0-24 18-42t42-18h600q24 0 42 18t18 42v600q0 24-18 42t-42
    18H180Zm0-60h600v-600H180v600Zm0-600v600-600Z"/></svg>
    )SVG";
static constexpr char svg_art_bookmarks[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M120-40v-700q0-24 18-42t42-18h480q24 0 42.5 18t18.5 42v700L420-167 120-40Zm60-91
    240-103 240 103v-609H180v609Zm600 1v-730H233v-60h547q24 0 42 18t18
    42v730h-60ZM180-740h480-480Z"/></svg>
    )SVG";
static constexpr char svg_art_calendar[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M180-80q-24 0-42-18t-18-42v-620q0-24 18-42t42-18h65v-60h65v60h340v-60h65v60h65q24 0
    42 18t18 42v620q0 24-18 42t-42 18H180Zm0-60h600v-430H180v430Zm0-490h600v-130H180v130Zm0 0v-130
    130Zm300 230q-17 0-28.5-11.5T440-440q0-17 11.5-28.5T480-480q17 0 28.5 11.5T520-440q0 17-11.5
    28.5T480-400Zm-160 0q-17 0-28.5-11.5T280-440q0-17 11.5-28.5T320-480q17 0 28.5 11.5T360-440q0
    17-11.5 28.5T320-400Zm320 0q-17 0-28.5-11.5T600-440q0-17 11.5-28.5T640-480q17 0 28.5
    11.5T680-440q0 17-11.5 28.5T640-400ZM480-240q-17 0-28.5-11.5T440-280q0-17 11.5-28.5T480-320q17
    0 28.5 11.5T520-280q0 17-11.5 28.5T480-240Zm-160 0q-17 0-28.5-11.5T280-280q0-17
    11.5-28.5T320-320q17 0 28.5 11.5T360-280q0 17-11.5 28.5T320-240Zm320 0q-17
    0-28.5-11.5T600-280q0-17 11.5-28.5T640-320q17 0 28.5 11.5T680-280q0 17-11.5
    28.5T640-240Z"/></svg>
    )SVG";
static constexpr char svg_art_contacts[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M700-490h40v-75l65 37 20-34-65-38 65-38-20-34-65 37v-75h-40v75l-65-37-20 34 65
    38-65 38 20 34 65-37v75ZM60-120q-24 0-42-18T0-180v-600q0-24 18-42t42-18h840q24 0 42 18t18
    42v600q0 24-18 42t-42 18H60Zm531-60h309v-600H60v600h7q44-69 112.5-109T329-329q81 0 149.5
    40T591-180ZM329-400q50 0 85-35t35-85q0-50-35-85t-85-35q-50 0-85 35t-35 85q0 50 35 85t85
    35ZM143-180h372q-35.606-42.275-84.303-65.637Q382-269 329-269t-101.5 23.5Q179-222
    143-180Zm186-280q-25.5 0-42.75-17.25T269-520q0-25.5 17.25-42.75T329-580q25.5 0 42.75
    17.25T389-520q0 25.5-17.25 42.75T329-460Zm151-20Z"/></svg>
    )SVG";
static constexpr char svg_art_data_table[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M180-120q-24 0-42-18t-18-42v-600q0-24 18-42t42-18h600q24 0 42 18t18 42v600q0
    24-18 42t-42 18H180Zm0-500h600v-160H180v160Zm0 220h600v-160H180v160Zm0
    220h600v-160H180v160Zm63-490v-60h60v60h-60Zm0 220v-60h60v60h-60Zm0
    220v-60h60v60h-60Z"/></svg>
    )SVG";
static constexpr char svg_art_drafts[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="m480-920 371 222q17 9 23 24.5t6 30.5v463q0 24-18 42t-42 18H140q-24
    0-42-18t-18-42v-463q0-15 6.5-30.5T109-698l371-222Zm0 466 336-197-336-202-336 202 336
    197Zm0 67L140-587v407h680v-407L480-387Zm0 207h340-680 340Z"/></svg>
    )SVG";
static constexpr char svg_art_favorite[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="m480-121-41-37q-105.768-97.121-174.884-167.561Q195-396 154-451.5T96.5-552Q80-597
    80-643q0-90.155 60.5-150.577Q201-854 290-854q57 0 105.5 27t84.5 78q42-54 89-79.5T670-854q89
    0 149.5 60.423Q880-733.155 880-643q0 46-16.5 91T806-451.5Q765-396 695.884-325.561
    626.768-255.121 521-158l-41 37Zm0-79q101.236-92.995 166.618-159.498Q712-426
    750.5-476t54-89.135q15.5-39.136 15.5-77.72Q820-709 778-751.5T670.225-794q-51.524 0-95.375
    31.5Q531-731 504-674h-49q-26-56-69.85-88-43.851-32-95.375-32Q224-794 182-751.5t-42
    108.816Q140-604 155.5-564.5t54 90Q248-424 314-358t166 158Zm0-297Z"/></svg>
    )SVG";
static constexpr char svg_art_folder[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M140-160q-24 0-42-18.5T80-220v-520q0-23 18-41.5t42-18.5h281l60 60h339q23 0 41.5
    18.5T880-680v460q0 23-18.5 41.5T820-160H140Zm0-60h680v-460H456l-60-60H140v520Zm0 0v-520
    520Z"/></svg>
    )SVG";
static constexpr char svg_art_label[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M840-480 671-241q-13 18-31 29.5T600-200H180q-24.75
    0-42.375-17.625T120-260v-440q0-24.75 17.625-42.375T180-760h420q22 0 40 11.5t31 29.5l169
    239Zm-75 0L611-700H180v440h431l154-220Zm-585 0v220-440 220Z"/></svg>
    )SVG";
static constexpr char svg_art_library[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M343-420h225v-60H343v60Zm0-90h395v-60H343v60Zm0-90h395v-60H343v60Zm-83 400q-24
    0-42-18t-18-42v-560q0-24 18-42t42-18h560q24 0 42 18t18 42v560q0 24-18 42t-42
    18H260Zm0-60h560v-560H260v560ZM140-80q-24
    0-42-18t-18-42v-620h60v620h620v60H140Zm120-740v560-560Z"/></svg>
    )SVG";
static constexpr char svg_art_objects[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M480-80q-27 0-47.5-13T406-129h-14q-24 0-42-18t-18-42v-143q-66-43-104-110t-38-148q0-121
    84.5-205.5T480-880q121 0 205.5 84.5T770-590q0 81-38 148T628-332v143q0 24-18 42t-42 18h-14q-6
    23-26.5 36T480-80Zm-88-109h176v-44H392v44Zm0-84h176v-40H392v40Zm-9-100h74v-137l-92-92 31-31 84
    84 84-84 31 31-92 92v137h74q60-28 96.5-87T710-590q0-97-66.5-163.5T480-820q-97 0-163.5
    66.5T250-590q0 71 36.5 130t96.5 87Zm97-176Zm0-48Z"/></svg>
    )SVG";
static constexpr char svg_art_pin[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="m634-448 86 77v60H510v241l-30
    30-30-30v-241H240v-60l80-77v-332h-50v-60h414v60h-50v332Zm-313 77h312l-59-55v-354H380v354l-59
    55Zm156 0Z"/></svg>
    )SVG";
static constexpr char svg_art_smiley[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M626-533q22.5 0 38.25-15.75T680-587q0-22.5-15.75-38.25T626-641q-22.5
    0-38.25 15.75T572-587q0 22.5 15.75 38.25T626-533Zm-292 0q22.5 0
    38.25-15.75T388-587q0-22.5-15.75-38.25T334-641q-22.5 0-38.25 15.75T280-587q0 22.5 15.75
    38.25T334-533Zm146 272q66 0 121.5-35.5T682-393H278q26 61 81 96.5T480-261Zm0 181q-83
    0-156-31.5T197-197q-54-54-85.5-127T80-480q0-83 31.5-156T197-763q54-54 127-85.5T480-880q83 0
    156 31.5T763-763q54 54 85.5 127T880-480q0 83-31.5 156T763-197q-54 54-127 85.5T480-80Zm0-400Zm0
    340q142.375 0 241.188-98.812Q820-337.625 820-480t-98.812-241.188Q622.375-820 480-820t-241.188
    98.812Q140-622.375 140-480t98.812 241.188Q337.625-140 480-140Z"/></svg>
    )SVG";
static constexpr char svg_art_support[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M480-80q-83 0-156-31.5T197-197q-54-54-85.5-127T80-480q0-83 31.5-156T197-763q54-54
    127-85.5T480-880q83 0 156 31.5T763-763q54 54 85.5 127T880-480q0 83-31.5 156T763-197q-54 54-127
    85.5T480-80Zm-121-80 63-150q-38-13-67.5-41.5T310-421l-150 60q31 71 82 123t117
    78Zm-50-378q16-41 45-70t67-42l-60-150q-75 31-127 83.5T160-598l149 60Zm171 178q50 0
    85-35t35-85q0-50-35-85t-85-35q-50 0-85 35t-35 85q0 50 35 85t85 35Zm121 200q69-28
    120-79.5T800-359l-150-62q-15 42-44.5 70.5T538-310l63 150Zm49-379
    150-62q-28-68-79.5-119.5T601-800l-61 150q38 13 66 41.5t44 69.5Z"/></svg>
    )SVG";
static constexpr char svg_art_work[] = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="0 -960 960 960">
    <path d="M140-120q-24 0-42-18t-18-42v-480q0-24 18-42t42-18h180v-100q0-24 18-42t42-18h200q24 0
    42 18t18 42v100h180q24 0 42 18t18 42v480q0 24-18 42t-42
    18H140Zm0-60h680v-480H140v480Zm240-540h200v-100H380v100ZM140-180v-480 480Z"/></svg>
    )SVG";

static const std::map<std::string, const char*> pool{
    {"FILE_NEW", svg_file_new},
    {"FILE_OPEN", svg_file_open},
    {"FILE_SAVE", svg_file_save},
    {"FILE_SAVE_AS", svg_file_save_as},
    {"FILE_QUIT", svg_file_quit},
    {"FILE_QUIT_2", svg_file_quit_2},
    {"EDIT_COPY", svg_edit_copy},
    {"EDIT_CUT", svg_edit_cut},
    {"EDIT_PASTE", svg_edit_paste},
    {"EDIT_SELECT_ALL", svg_edit_select_all},
    {"EDIT_UNDO", svg_edit_undo},
    {"EDIT_REDO", svg_edit_redo},
    {"HELP_INFO", svg_help_info},
    {"MISC_FONT", svg_misc_font},
    {"MISC_LOCKED", svg_misc_locked},
    {"MISC_UNLOCKED", svg_misc_unlocked},
    {"MISC_KEY", svg_misc_key},
    {"MISC_SETTINGS", svg_misc_settings},
    {"MISC_ITEM_ADD", svg_misc_item_add},
    {"MISC_ITEM_EDIT", svg_misc_item_edit},
    {"MISC_ITEM_EDIT_2", svg_misc_item_edit_2},
    {"MISC_ITEM_DELETE", svg_misc_item_delete},
    {"MISC_CREATE_FOLDER", svg_misc_create_folder},
    {"MISC_EXPAND", svg_misc_expand},
    {"MISC_COLLAPSE", svg_misc_collapse},
    {"MISC_CHECK", svg_misc_check},
    {"MISC_UP", svc_misc_up},
    {"MISC_DOWN", svc_misc_down},
    {"MISC_BUILD", svg_misc_build},
    {"ART_ARTICLE", svg_art_article},
    {"ART_BOOKMARKS", svg_art_bookmarks},
    {"ART_CALENDAR", svg_art_calendar},
    {"ART_CONTACTS", svg_art_contacts},
    {"ART_DATA_TABLE", svg_art_data_table},
    {"ART_DRAFTS", svg_art_drafts},
    {"ART_FAVORITE", svg_art_favorite},
    {"ART_FOLDER", svg_art_folder},
    {"ART_LABEL", svg_art_label},
    {"ART_LIBRARY", svg_art_library},
    {"ART_OBJECTS", svg_art_objects},
    {"ART_PIN", svg_art_pin},
    {"ART_SMILEY", svg_art_smiley},
    {"ART_SUPPORT", svg_art_support},
    {"ART_WORK", svg_art_work}
};

class IconPool {
public:
    static std::optional<const char*> getSVGIconByName(const std::string& name) {
        if (const auto it = pool.find(name); it != pool.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    static wxBitmapBundle getBitmapBundleByName(const std::string& name, const int& size) {
        if (const auto svg = getSVGIconByName(name); svg.has_value()) {
            return wxBitmapBundle::FromSVG(*svg, wxSize(size, size));
        }
        return wxNullBitmap;
    }
    static std::vector<std::string> getIconNamesAll() {
        std::vector<std::string> names{};
        for (const auto& key : pool | std::views::keys) {
            names.push_back(key);
        }
        return names;
    }
};
