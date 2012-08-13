#!/usr/bin/env python

import os, numpy
import Image

# -----------------------------------------------------

def png2rgba(namespace, filenames):

    fdH = open("%s.h" % namespace, "w")
    fdH.write("/* (Auto-generated binary data file). */\n")
    fdH.write("\n")
    fdH.write("#ifndef BINARY_%s_H\n" % namespace.upper())
    fdH.write("#define BINARY_%s_H\n" % namespace.upper())
    fdH.write("\n")
    fdH.write("namespace %s\n" % namespace)
    fdH.write("{\n")

    fdC = open("%s.cpp" % namespace, "w")
    fdC.write("/* (Auto-generated binary data file). */\n")
    fdC.write("\n")
    fdC.write("#include \"%s.h\"\n" % namespace)
    fdC.write("\n")

    tempIndex = 1

    for filename in filenames:
        shortFilename = filename.rsplit(os.sep, 1)[-1].split(".", 1)[0]

        png      = Image.open(filename)
        pngNumpy = numpy.array(png)
        pngData  = pngNumpy.tolist()
        pngData.reverse()

        height = len(pngData)
        for dataBlock in pngData:
            width = len(dataBlock)
            break

        fdH.write("    extern const char* %sData;\n" % shortFilename)
        fdH.write("    const unsigned int %sDataSize = %i;\n" % (shortFilename, width * height * 4))
        fdH.write("    const unsigned int %sWidth    = %i;\n" % (shortFilename, width))
        fdH.write("    const unsigned int %sHeight   = %i;\n" % (shortFilename, height))

        if tempIndex != len(filenames):
            fdH.write("\n")

        fdC.write("static const unsigned char temp%i[] = {\n" % tempIndex)

        curColumn = 1
        fdC.write(" ")

        for dataBlock in pngData:
            if curColumn == 0:
                fdC.write(" ")

            for data in dataBlock:
                r, g, b, a = data
                fdC.write(" %3u, %3u, %3u, %3u," % (b, g, r, a))

                if curColumn > 20:
                    fdC.write("\n ")
                    curColumn = 1
                else:
                    curColumn += 1

        fdC.write("};\n")
        fdC.write("const char* %s::%sData = (const char*)temp%i;\n" % (namespace, shortFilename, tempIndex))

        if tempIndex != len(filenames):
            fdC.write("\n")

        tempIndex += 1

    fdH.write("}\n")
    fdH.write("\n")
    fdH.write("#endif // BINARY_%s_H\n" % namespace.upper())
    fdH.write("\n")
    fdH.close()

    fdC.write("\n")
    fdC.close()

# -----------------------------------------------------

filenames = [
    "/home/falktx/Personal/FOSS/GIT/distrho/plugins/3BandEQ/source/artwork/background.png",
    "/home/falktx/Personal/FOSS/GIT/distrho/plugins/3BandEQ/source/artwork/knob.png",
    "/home/falktx/Personal/FOSS/GIT/distrho/plugins/3BandEQ/source/artwork/slider.png"
  ]

png2rgba("DistrhoArtwork", filenames)
