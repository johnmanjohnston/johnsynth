/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Helvetica_ttf;
    const int            Helvetica_ttfSize = 312960;

    extern const char*   HelveticaLight_ttf;
    const int            HelveticaLight_ttfSize = 161716;

    extern const char*   SpaceMonoRegular_ttf;
    const int            SpaceMonoRegular_ttfSize = 90904;

    extern const char*   empty_panel_png;
    const int            empty_panel_pngSize = 1052;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 4;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
