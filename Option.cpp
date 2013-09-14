// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QStringList>
#include <QDebug>
#include "Option.hpp"

namespace {

const Default setDefault = Default();

Option opts[] = {

    Option("Data convention", "DATARULE")
    << "German dip directon" << "G" << setDefault
    << "Right hand rule" << "R",


    Option("Plot type", "PLOT")
    << "Angelier plot" << "A" << setDefault
    << "Hoeppner pole point" << "H",


    Option("Projection type", "PLOTTYPE")
    << "Schmidt" << "S" << setDefault
    << "Wulff"   << "W",


    Option("Hemisphere", "HEMISPHERE")
    << "Upper" << "U"
    << "Lower" << "L" << setDefault,


    Option("Bedding & palaeonorth correction", "TILTING")
    << "Re-tilt with the bedding" << "B"
    << "Only palaeonorth direction" << "P"
    << "Both" << "A" << setDefault,


    Option("Sort by groups as well", "GROUP")
    << "Yes" << "Y" << setDefault
    << "No"  << "N",


    Option("Cluster numbers", "CLUSTERNUMBER")
    << "Ideal" << "A"
    << "Don\'t use" << "N" << setDefault
    << "2" << "2"
    << "3" << "3"
    << "4" << "4"
    << "5" << "5"
    << "6" << "6"
    << "7" << "7"
    << "8" << "8"
    << "9" << "9",


    Option("Labelling", "LABELING")
    << "Yes" << "Y"
    << "No"  << "N" << setDefault,


    Option("Inversion methodology", "INVERSION")
    << "NDA after Sprang (1972)" << "D" << setDefault
    << "PTN after Turner (1953)" << "P"
    << "Fry (1999)" << "F"
    << "Shan et al (2003)" << "S"
    << "Michael (1984)"  << "M"
    << "Angelier (1990)" << "A"
    << "Mostafa (2005)"  << "O"
    << "None"            << "N",

    Option("Stress estimator in clustering", "RUP_CLUSTERING")
    << "Don\'t use"               << "N" << setDefault
    << "Use angular misfit (ANG)" << "A"
    << "Relative upsilon (RUP)"   << "R",

    Option("Virtual symmetrical data set", "VIRTUAL")
    << "Yes" << "Y"
    << "No"  << "N" << setDefault,

    Option("Ideal movement direction display", "IDEALMOVEMENT")
    << "Yes" << "Y"
    << "No"  << "N" << setDefault,

    // TODO Spinbox would be more appropriate
    Option("Maximum stress & slickenside direction angle", "STRESSANGLE")
    << "10" << "10"
    << "15" << "15"
    << "20" << "20"
    << "25" << "25"
    << "30" << "30" << setDefault
    << "35" << "35"
    << "40" << "40"
    << "45" << "45"
    << "50" << "50"
    << "55" << "55"
    << "60" << "60"
    << "65" << "65"
    << "70" << "70"
    << "75" << "75"
    << "80" << "80",


    Option("Fracture weight point statistics", "BINGHAM")
    << "Bingham statistics" << "B" << setDefault
    << "Not needed" << "N",


    // TODO Spinbox would be more appropriate
    Option("Line width used on stereonets in points", "LINEWIDTH")
    << "0.1" << "1"
    << "0.2" << "2"
    << "0.3" << "3"
    << "0.4" << "4"
    << "0.5" << "5"
    << "0.6" << "6" << setDefault
    << "0.7" << "7"
    << "0.8" << "8"
    << "0.9" << "9"
    << "1.0" << "0",


    Option("Type of the rose plot", "ROSETYPE")
    << "Symmetric"  << "S" << setDefault
    << "Asymmetric" << "A",

    Option("Rose diagram according to", "ROSEDIRECTION")
    << "Strike directions" << "S" << setDefault
    << "Dip directions"    << "D",

    Option("Bin size for rose plot in degrees", "ROSEBINNING")
    <<  "2.5" << "A"
    <<  "5.0" << "B"
    << "10.0" << "C" << setDefault
    << "22.5" << "D",

    Option("Density contouring on stereonet", "CONTOURING")
    << "None"                  << "N" << setDefault
    << "Schmidt 1% method"     << "S"
    << "Kamb\'s (1959) method" << "K",

    Option("Grayscale", "GRAYSCALE")
    << "Coloured output" << "N" << setDefault
    << "Grayscale mode" << "Y"

};

}

const Option* Option::getOpts() {

    int n = getOptSize();

    for (int i=0; i<n; ++i) {

        opts[i].checkConsistency();
    }

    return opts;
}

int Option::getOptSize() {

    return sizeof(opts) / sizeof(opts[0]);
}

Option::Option(const QString& guiKey, const QString& cliKey)
:   key(guiKey),
    cliKey(cliKey),
    defaultElem(-1)
{

}

Option& Option::operator<<(const QString& value_str) {

    if (cliValues.size() == values.size()) {

        values.append(value_str);
    }
    else {

        cliValues.append(value_str);
    }

    return *this;
}

Option& Option::operator<<(const Default& ) {

    defaultElem = values.size() - 1;

    return *this;
}

void Option::checkConsistency() const {

    Q_ASSERT( values.size()==cliValues.size() );

    Q_ASSERT( 0 <= defaultElem);

    Q_ASSERT( defaultElem < values.size() );

}

QString Option::toCLIString(int i) const {

    return cliKey + ":\t" + cliValues.at(i);
}

int Option::toIndex(const QString& cliLine) const {

    int index = defaultElem;

    QStringList opt = cliLine.split(":\t", QString::SkipEmptyParts);

    if (opt.size()==2 && opt.at(0)==cliKey) {

        int pos = cliValues.indexOf(opt.at(1));

        index = (pos>=0) ? pos : defaultElem;

        //qDebug() << key << index << "(" << defaultElem << ")";
    }

    return index;
}

