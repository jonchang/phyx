#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <getopt.h>

using namespace std;

#include "tgen.h"
#include "utils.h"
#include "log.h"

void print_help() {
    cout << "Generate all tree topologies for n taxa." << endl;
    cout << "Currently only unrooted, but rooted coming. As are random trees." << endl;
    cout << endl;
    cout << "Usage: pxtgen [OPTION]... " << endl;
    cout << endl;
    cout << " -n, --ntax=INT      number of taxa" << endl;
    cout << " -r, --rooted        whether generated trees are rooted (default: false)" << endl;
    cout << " -l, --label=STRING  prefix label for taxon names (default: 't')" << endl;
    cout << " -o, --outf=FILE     output file, stout otherwise" << endl;
//    cout << " -x, --seed=INT      random number seed, clock otherwise" << endl;
    cout << " -h, --help          display this help and exit" << endl;
    cout << " -V, --version       display version and exit" << endl;
    cout << endl;
    cout << "Report bugs to: <https://github.com/FePhyFoFum/phyx/issues>" << endl;
    cout << "phyx home page: <https://github.com/FePhyFoFum/phyx>" << endl;
}

string versionline("pxtgen 0.1\nCopyright (C) 2019 FePhyFoFum\nLicense GPLv3\nwritten by Joseph W. Brown, Stephen A. Smith (blackrim)");

static struct option const long_options[] =
{
    {"ntax", required_argument, NULL, 'n'},
    {"rooted", no_argument, NULL, 'r'},
    {"label", required_argument, NULL, 'l'},
    {"outf", required_argument, NULL, 'o'},
//    {"seed", required_argument, NULL, 'x'},
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'V'},
    {NULL, 0, NULL, 0}
};

int main(int argc, char * argv[]) {
    
    log_call(argc, argv);
    
    int ntax = 0;
    bool rooted = false;
    bool outfileset = false;
    string lprefix = "t";
    char * outf = NULL;
//    int seed = -1;
    
    while (1) {
        int oi = -1;
        int c = getopt_long(argc, argv, "n:rl:o:hV", long_options, &oi);
        if (c == -1) {
            break;
        }
        switch(c) {
            case 'n':
                ntax = string_to_int(optarg, "-n");
                break;
            case 'r':
                rooted = true;
                break;
            case 'l':
                lprefix = strdup(optarg);
                break;
            case 'o':
                outfileset = true;
                outf = strdup(optarg);
                break;
//            case 'x':
//                seed = string_to_int(optarg, "-x");
//                break;
            case 'h':
                print_help();
                exit(0);
            case 'V':
                cout << versionline << endl;
                exit(0);
            default:
                print_error(argv[0], (char)c);
                exit(0);
        }
    }
    
    if (ntax == 0) {
        cout << "You have to set the number of taxa -n. Exiting." << endl;
        exit(0);
    }else if (ntax < 3) {
        cout << "The number of taxa -n must be >= 3. Exiting." << endl;
        exit(0);
    }else if (ntax > 10) {
        cout << "The number of taxa -n is limited to 10. Exiting." << endl;
        exit(0);
    }
    
    ostream * poos = NULL;
    ofstream * ofstr = NULL;
    
    if (outfileset == true) {
        ofstr = new ofstream(outf);
        poos = ofstr;
    } else {
        poos = &cout;
    }
    
    TopologyGenerator TG(ntax, rooted, lprefix);
    TG.get_newicks(poos);
    
    if (outfileset) {
        ofstr->close();
        delete poos;
    }
    return EXIT_SUCCESS;
}
