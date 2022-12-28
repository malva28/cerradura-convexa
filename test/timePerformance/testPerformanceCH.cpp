#include <iostream>
#include <fstream>
#include <convex_hull.h>
#include "../reg_poly_gen.cpp"
#include "timeutil.cpp"

namespace fileSetup
{
    const int nInc{ 27 };
    const int nVert{ 21 };
    const int totalVert{ 100000 };
    const int divInc{ 10 };

    const std::array<int, 27> incSizes{
       1000,    2000,    3000,    4000,    5000,    6000,    7000,    8000,    9000,
      10000,   20000,   30000,   40000,   50000,   60000,   70000,   80000,   90000,
      100000,  200000,  300000,  400000,  500000,  600000,  700000,  800000,  900000};

    std::array<int, 27> incBorder;

    const std::array<int,21> vertSizes{
            3, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000,
            50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, totalVert
    };

    std::array<std::vector<Punto<double>>, 27> ptInc;
    std::array<std::vector<Punto<double>>, 21> ptVert;
};

int pow10(int power, int res=1)
{
    if (power > 0)
    {
        return res;
    }
    return pow10(power-1, res*10);
}


void genDataTest()
{
    for(int k{ }; k < fileSetup::nInc; k++)
    {
        int total{ fileSetup::incSizes[k] };
        int ptBorder{ total/fileSetup::divInc };
        fileSetup::incBorder[k] = ptBorder;

        int ptInside{ ptBorder*(fileSetup::divInc-1) };
        fileSetup::ptInc[k] = { gen_reg_points_inside(ptBorder, ptInside, MyRandom::mersenne) };
        shuffle(fileSetup::ptInc[k]);
    }

    for(int k{ }; k < fileSetup::nVert; k++)
    {
        int ptInside{ fileSetup::totalVert - fileSetup::vertSizes[k] };
        fileSetup::ptVert[k] = { gen_reg_points_inside(fileSetup::vertSizes[k], ptInside, MyRandom::mersenne) };
        shuffle(fileSetup::ptVert[k]);
    }

};

class FileDataManager
{
private:
    std::string m_filename;
    std::ofstream m_outfile;
    std::string m_sep{ ", " };

public:
    FileDataManager(std::string filename)
    : m_filename{ filename }
    {};

    ~FileDataManager()
    {
        close();
    };

    std::ofstream& writeData(std::initializer_list<std::string> fieldNames )
    {
        for (std::string aField: fieldNames)
        {
            m_outfile << aField << m_sep;
        }
        m_outfile << '\n';
        return m_outfile;
    }

    std::ofstream& write(std::string txt)
    {
        m_outfile << txt;
        return m_outfile;
    }

    auto open()
    {
        return m_outfile.open(m_filename, std::ios::out);
    }

    void close()
    {
        m_outfile.close();
    }
};


void timeJarvisIncrementalCH()
{
    // gift wrap

    std::cout << "===Gift Wrap Algorithm===\n";

    FileDataManager fout{ "jarvis_time_increasing_points.csv" };
    fout.open();
    fout.writeData({"total_pts", "pts_in_border", "time[s]" });

    for(int i { 0 }; i < fileSetup::nInc; i++ )
    {
        auto nPts{ fileSetup::ptInc[i].size() };
        auto nPtsBorder { fileSetup::incBorder[i] };

        std::cout << "===Gift Wrap Algorithm===\n";
        std::cout << "   +-- Testing for " << nPts << " total points and " << nPtsBorder << " in hull\n";

        // start clock
        Clock clock;
        giftWrapping(fileSetup::ptInc[i]);
        double timeSeconds{ clock.stop() };

        fout.writeData({std::to_string(nPts), std::to_string(nPtsBorder), std::to_string(timeSeconds)});
    }
    fout.close();

}

void timeGrahamIncrementalCH()
{
    // gift wrap

    std::cout << "===Graham Scan Algorithm===\n";

    FileDataManager fout{ "graham_scan_increasing_points.csv" };
    fout.open();
    fout.writeData({"total_pts", "pts_in_border", "time[s]" });

    for(int i { 0 }; i < fileSetup::nInc; i++ )
    {
        auto nPts{ fileSetup::ptInc[i].size() };
        auto nPtsBorder { fileSetup::incBorder[i] };

        std::cout << "===Graham Scan Algorithm===\n";
        std::cout << "   +-- Testing for " << nPts << " total points and " << nPtsBorder << " in hull\n";

        // start clock
        Clock clock;
        // Poligono<double> pol { grahamScan(fileSetup::ptInc[i]) };
        std::vector<int> polIn { grahamScanIndex(fileSetup::ptInc[i]) };
        double timeSeconds{ clock.stop() };

        //for(int i{ }; i < polIn; i++)
        //{

        //}
        //std::cout << pol << '\n';



        fout.writeData({std::to_string(nPts), std::to_string(nPtsBorder), std::to_string(timeSeconds)});
    }
    fout.close();

}

void timeJarvisVerticesCH()
{
    // gift wrap

    std::cout << "===Gift Wrap Algorithm===\n";

    FileDataManager fout{ "jarvis_time_vertices.csv" };
    fout.open();
    fout.writeData({"total_pts", "pts_in_border", "time[s]" });

    auto nPts{ fileSetup::totalVert };
    for(int i { 0 }; i < fileSetup::nVert; i++ )
    {

        auto nPtsBorder { fileSetup::vertSizes[i] };

        std::cout << "===Gift Wrap Algorithm===\n";
        std::cout << "   +-- Testing for " << nPts << " total points and " << nPtsBorder << " in hull\n";

        // start clock
        Clock clock;
        giftWrapping(fileSetup::ptVert[i]);
        double timeSeconds{ clock.stop() };



        fout.writeData({std::to_string(nPts), std::to_string(nPtsBorder), std::to_string(timeSeconds)});
    }
    fout.close();

}

void timeGrahamVerticesCH()
{
    // gift wrap

    std::cout << "===Graham Scan Algorithm===\n";

    FileDataManager fout{ "graham_time_vertices.csv" };
    fout.open();
    fout.writeData({"total_pts", "pts_in_border", "time[s]" });

    auto nPts{ fileSetup::totalVert };
    for(int i { 0 }; i < fileSetup::nVert; i++ )
    {

        auto nPtsBorder { fileSetup::vertSizes[i] };

        std::cout << "===Graham Scan Algorithm===\n";
        std::cout << "   +-- Testing for " << nPts << " total points and " << nPtsBorder << " in hull\n";

        // start clock
        Clock clock;
        grahamScan(fileSetup::ptVert[i]);
        double timeSeconds{ clock.stop() };



        fout.writeData({std::to_string(nPts), std::to_string(nPtsBorder), std::to_string(timeSeconds)});
    }
    fout.close();

}


int main()
{
    std::cout << "Building Test Point Data...\n";
    genDataTest();
    std::cout << "Running algorithms...\n";

    timeJarvisIncrementalCH();
    timeJarvisVerticesCH();
    timeGrahamIncrementalCH();
    timeGrahamVerticesCH();
    return 0;
}