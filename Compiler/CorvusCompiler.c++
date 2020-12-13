#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string file = "%no_specified_file%";

int main(int argc, char *argv[]) {

    ofstream generatedc;
    generatedc.open("corvuscompilerc.c");

    generatedc << "#include <stdio.h>" << endl;
    generatedc << "int main() {" << endl;

    int i = 1;
    while(i < argc) {

        if(((string) argv[i]).compare("-i") == 0) {

            i++;
            cout << "[DEBUG] Setting file to " << argv[i] << endl;
            file = argv[i];

        }

        cout << "[DEBUG] Arg: " << argv[i] << endl;

        i++;

    }

    if(!(file == "%no_specified_file%")) {

        string line;

        ifstream corvsrcfile;
        corvsrcfile.open(file);

        while(getline(corvsrcfile, line)) {

            if(line.rfind("print ",0) == 0) {

                generatedc << "printf(\"" << line.substr(6,line.length()) << "\");" << endl;

            }


        }

        corvsrcfile.close();


    } else {

        cout << "[DEBUG] No file specified." << endl;

    }


    generatedc << "}" << endl;


    generatedc.close();

    system("gcc corvuscompilerc.c");

    remove("corvuscompilerc.c");

}