/* fjson - format JSON

Usage: fjson input.json

Output is sent to stdout
*/

/*
The MIT License (MIT)

Copyright (c) 2013 PapaCharlie9

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <cstdio>
#include <string>

static void NewLineAndIndent(int indent) {
    ::printf("\n");
    for (int i = 0; i < indent; ++i) {
        ::fputc(' ', stdout);
        ::fputc(' ', stdout);
    }
}

int main(int argc, char** argv) {
    std::string fileName;

    --argc;
    ++argv;

    if (argc == 0) {
        ::fprintf(stderr, "No input file specified!\n");
        return -1;
    }

    fileName = *argv;

    FILE* ip = nullptr;
    if ((ip = ::fopen(fileName.c_str(), "r")) == nullptr) {
        std::string msg = fileName + ": " + ::strerror(errno) + "\n";
        ::fprintf(stderr, msg.c_str());
        return -1;
    }

    int indent = 0;

    int c = 0;

    while ((c = ::fgetc(ip)) != EOF) {
        // prefix
        switch (c) {
            case '{': {
                NewLineAndIndent(indent);
                break;
                }
            case '[': {
                ::fputc(' ', stdout);
                break;
                }
            case ']': {
                if (indent > 0) --indent;
                NewLineAndIndent(indent);
                break;
                }
            case '}': {
                if (indent > 0) --indent;
                NewLineAndIndent(indent);
                break;
                }
            default:;
        }

        // infix
        ::fputc(c, stdout);

        // suffix
        switch (c) {
            case '{': {
                ++indent;
                NewLineAndIndent(indent);
                break;
                }
            case '[': {
                ++indent;
                NewLineAndIndent(indent);
                break;
                }
            case ',': {
                NewLineAndIndent(indent);
                break;
                }
            /*
            case ']':
                //::printf("\n");
                break;
            case '}':
                //if (indent > 0) --indent;
                //NewLineAndIndent(indent);
                break;
            */
            case ':': {
                fputc(' ', stdout);
                break;
                }
            default:;
        }
    }
    fflush(ip);
    fclose(ip);
    return(0);
}