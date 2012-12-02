// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QStringList>
#include "Option.hpp"

namespace {

Option opts[] = {

    Option("Data convention") << "German dip directon" << setDefault << "Right hand rule",

    Option("Plot type") << "Angelier plot" << setDefault << "Hoeppner pole point",

    Option("Projection type") << "Schmidt" << setDefault << "Wulff",

    Option("Hemisphere") << "Upper" << "Lower" << setDefault,

    Option("Bedding & palaeonorth correction") << "Re-tilt with the bedding"
                                               << "Only palaeonorth direction"
                                               << "Both" << setDefault,

    Option("Sort by groups as well") << "Yes" << setDefault << "No" ,

    Option("Cluster numbers") << "Ideal" << "Don\'t use" << setDefault <<"2"<<"3"<<"4"<<"5"
                                                                       <<"6"<<"7"<<"8"<<"9",

    Option("Labelling") << "Yes" << "No" << setDefault,

    Option("Inversion methodology") << "NDA after Sprang (1972)" << setDefault
                                    << "PTN after Turner (1953)"
                                    << "Fry (1999)"
                                    << "Shan et al (2003)"
                                    << "Michael (1984)"
                                    << "Angelier (1990)"
                                    << "Mostafa (2005)",

    Option("Virtual symmetrical data set") << "Yes" << "No" << setDefault,

    Option("Ideal movement direction display") << "Yes" << "No" << setDefault,

    // TODO Spinbox would be more appropriate
    Option("Maximum stress & slickenside direction angle") <<"10"<<"15"<<"20"<<"25"<<"30" << setDefault
                                                           <<"35"<<"40"<<"45"<<"50"<<"55"
                                                           <<"60"<<"65"<<"70"<<"75"<<"80",

    Option("Fracture weight point statistics") << "Bingham statistics" << setDefault << "Not needed" ,

    // TODO Spinbox would be more appropriate
    Option("Line width used on stereonets in points") <<"0.1"<<"0.2"<<"0.3"
                                                      <<"0.4"<<"0.5"<<"0.6" << setDefault
                                                      <<"0.7"<<"0.8"<<"0.9"
                                                      <<"1.0",

    Option("Type of the rose plot") << "Symmetric" << setDefault << "Asymmetric",

    Option("Bin size for rose plot in degrees") << "2.5" << "5.0" << "10.0" << setDefault << "22.5"

};

}

const Option* Option::getOpts() {

    return opts;
}

int Option::getOptSize() {

    return sizeof(opts) / sizeof(opts[0]);
}

Option::Option(const QString& key_str)
:   key(key_str),
    defaultElem(-1)
{

}

Option& Option::operator<<(const QString& value_str) {

    values.append(value_str);

    return *this;
}

Option& Option::operator<<(const Default& ) {

    defaultElem = values.size() - 1;

    return *this;
}
