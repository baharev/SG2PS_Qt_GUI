// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef OPTION_HPP
#define OPTION_HPP

struct Option {

    Option(const QString& key_str) : key(key_str) { }

    Option& operator<<(const QString& value_str) { values.append(value_str); return *this; }

    QString key;

    QStringList values;
};

Option opts[] = {

    Option("Data convention") << "German dip directon" << "right hand rule",

    Option("Plot type") << "Angelier plot" << "Hoeppner pole point",

    Option("Projection type") << "Schmidt" << "Wulff",

    Option("Hemisphere") << "upper" << "lower",

    Option("Bedding & palaeonorth correction") << "re-tilt with the bedding"
                                               << "only palaeonorth direction"
                                               << "both",

    // FIXME Shouldn't it be sort???
    Option("Separate by locality, datatype and groups") << "yes" << "no" ,

    // FIXME Arbitrary number?
    Option("Cluster numbers") << "ideal" << "don't use" <<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9",

    Option("Labelling") << "yes" << "no" ,

    Option("Inversion methodology") << "NDA after Sprang (1972)"
                                    << "PTN after Turner (1953)"
                                    << "Fry (1999)"
                                    << "Shan et al (2003)"
                                    << "Michael (1984)"
                                    << "Angelier (1990)"
                                    << "Mostafa (2005)",

    Option("Virtual symmetrical data set") << "yes" << "no" ,

    Option("Ideal movement direction display") << "yes" << "no" ,

    // FIXME Arbitrary number?
    Option("Maximum stress & slickenside direction angle") << "10" << "30" << "80",

    Option("Fracture weight point statistics") << "Bingham statistics" << "not needed" ,

    // FIXME Arbitrary number?
    Option("Line width used on stereonets in points") << "0.1" << "0.6" << "1.0",

    Option("Type of the rose plot") << "symmetric" << "asymmetric",

    Option("Bin size for rose plot in degrees") << "2.5" << "4.0" << "10.0" << "22.5"

};

#endif // OPTION_HPP
