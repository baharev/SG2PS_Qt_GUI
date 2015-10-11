// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QStringList>
#include <QDebug>
#include "Option.hpp"

namespace {

const Default setDefault = Default();

// Keep this as the first item (index 0)
// It will be treated as special, and not shown

Option mode_opts[] = {

    Option("Field or well data", "WELLDATA")
    << "Field" << "N" << setDefault
    << "Well"  << "Y"
};

Option conv_opts[] = {

    Option("Data convention", "DATARULE")
    << "German dip directon" << "G" << setDefault
    << "Right hand rule"     << "R",

    Option("Plot type", "PLOT")
    << "Angelier plot"       << "A" << setDefault
    << "Hoeppner pole point" << "H",

    Option("Projection type", "PLOTTYPE")
    << "Schmidt" << "S" << setDefault
    << "Wulff"   << "W",

    Option("Hemisphere", "HEMISPHERE")
    << "Upper" << "U"
    << "Lower" << "L" << setDefault,

    Option("Contouring on stereonet", "CONTOURING")
    << "None"                       << "N" << setDefault
    //<< "Schmidt 1% method"      << "S"
    //<< "Kamb\'s (1959) method"  << "K"
    << "Dip direction / bearing"    << "D"
    << "Strike direction / bearing" << "S"
    << "Plane normal / bearing"     << "O"
    << "Striae bearing / bearing"   << "B",

    Option("Bedding & palaeonorth correction", "TILTING")
    << "Re-tilt with bedding" << "B"
    << "Only palaeonorth"     << "P"
    << "Both"                 << "A" << setDefault
};

Option inver_opts[] = {

    Option("Inversion methodology", "INVERSION")
    << "NDA after Spang (1972)"  << "D" << setDefault
    << "PTN after Turner (1953)" << "P"
    << "Fry (1999)"      << "F"
    << "Shan et al (2003)" << "S"
    << "Michael (1984)"  << "M"
    << "Angelier (1990)" << "A"
    << "Mostafa (2005)"  << "O"
    << "Brute force"     << "B"
    << "None"            << "N",

    Option("Bingham statistics", "BINGHAM")
    << "Yes" << "B" << setDefault
    << "No"  << "N",

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

    Option("Forced Andersonian stress conditions", "VIRTUAL")
    << "Yes" << "Y"
    << "No"  << "N" << setDefault
};

Option group_opts[] = {

    Option("Use user-defined groups", "GROUP")
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

    Option("Clustering by stress estimator", "RUP_CLUSTERING")
    << "Don\'t use"             << "N" << setDefault
    << "Angular misfit (ANG)"   << "A"
    << "Relative upsilon (RUP)" << "R",

    Option("Separation of the output by", "GROUPSEPARATION")
    << "Don\'t separate"     << "I" << setDefault
    << "User-defined groups" << "G"
    << "K-means clustering"  << "K"
    << "RUP/ANG clustering"  << "R",

    Option("Group re-processing", "INPUTGROUP")
    << "Ignore groups"             << "N" << setDefault
    << "Original user-defined"     << "F"
    << "Former k-means clustering" << "S"
    << "Former RUP/ANG clustering" << "T",
};

Option rose_opts[] = {

    Option("Rose plot type", "ROSETYPE")
    << "Bidirectional"  << "S" << setDefault
    << "Unidirectional" << "A",

    Option("Plot rose diagram according to", "ROSEDIRECTION")
    << "Strike directions" << "S" << setDefault
    << "Dip directions"    << "D",

    Option("Bin size for rose plot in degrees", "ROSEBINNING")
    <<  "2.5" << "A"
    <<  "5.0" << "B"
    << "10.0" << "C" << setDefault
    << "22.5" << "D"
};

Option plot_opts[] = {

    Option("Display resolved shear direction", "IDEALMOVEMENT")
    << "Yes" << "Y"
    << "No"  << "N" << setDefault,

    Option("Labeling", "LABELING")
    << "Yes" << "Y"
    << "No"  << "N" << setDefault,

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

    Option("Coloring by", "COLORING")
    << "Uniform black"       << "I" << setDefault
    << "Color code"          << "C"
    << "User-defined groups" << "G"
    << "K-means clustering"  << "K"
    << "RUP/ANG clustering"  << "R",

    Option("Grayscale", "GRAYSCALE")
    << "Coloured output" << "N" << setDefault
    << "Grayscale mode"  << "Y"

};

Option well_opts[] = {

    Option("Bin size measured in", "WELLINTERVAL")
    << "meters"      << "M" << setDefault
    << "data points" << "D",

    Option("Bin size", "WELLINTERVAL_LENGTH")
    <<    "1" <<    "1"
    <<    "2" <<    "2"
    <<    "5" <<    "5"
    <<   "10" <<   "10"
    <<   "20" <<   "20"
    <<   "50" <<   "50"
    <<  "100" <<  "100" << setDefault
    <<  "200" <<  "200"
    <<  "500" <<  "500"
    << "1000" << "1000"
    << "2000" << "2000"
    << "5000" << "5000",

    Option("Bin midpoint", "WELLINTERVAL_MIDDLE")
    << "average depth" << "A"
    << "median depth"  << "M" << setDefault

};

template <typename T, int N>
QVector<T> qVec(T (&arr)[N]) {
    QVector<T> vec;
    vec.reserve(N);
    for (int i=0; i<N; ++i) {
        vec.push_back(arr[i]);
    }
    return vec;
}

template <typename T, typename U, int N>
void add(QVector<T>& vec, const char* name, U (&options)[N]) {
    vec.push_back( qMakePair(QString(name), qVec(options)) );
}

QVector<OptionGroup> createOptionGroups() {
    QVector<OptionGroup> vec;

    add(vec, "Processing mode",      mode_opts);

    add(vec, "Well data processing", well_opts);
    add(vec, "Group management",     group_opts);
    add(vec, "Plotting",             plot_opts);

    add(vec, "Conventions",          conv_opts);
    add(vec, "Inversion",            inver_opts);
    add(vec, "Rose diagram",         rose_opts);

    return vec;
}

const QVector<OptionGroup> optionGroups( createOptionGroups() );

} // end of anonymous namespace

const QVector<OptionGroup>& getOptionGroups() {
    return optionGroups;
}

int numberOfGroups() {
    return optionGroups.size();
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
