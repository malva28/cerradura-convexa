import re
import matplotlib.pyplot as plt
import numpy as np
import os
import argparse
import sys

num_pattern = r'[-]?\d+(\.\d+)?([e][\+\-]\d+)?'

base = "results"

filenames = [
    "graham_scan_increasing_points.csv",
    "jarvis_time_increasing_points.csv",
    "graham_time_vertices.csv",
    "jarvis_time_vertices.csv"
]

for i in range(len(filenames)):
    filenames[i] = os.path.join(base, filenames[i])


def _check_pattern(line, pattern):
    """
    Checks that line matches the iss_pattern. Returns True if it does
    and also adds info about if it is a commentary or not.
    Returns False otherwise
    """
    r = re.match(pattern, line)
    if r:
        return r.groupdict()
    else:
        return False


def is_point_time(line):
    """
    """
    constant_pattern = r'(?P<total>\d+)[,]?\s+(?P<border>\d+)[,]?\s+(?P<time>{})\s*'.format(num_pattern)
    return _check_pattern(line, constant_pattern)


def transform_coord_data(coord_dict):
    """
    Transforms a coordinate dict's fields to their corresponding
    numeric types. coord_dict is possibly a result from calling
    is_coordinate_definition
    """
    int_keys     = ["total","border"]
    numeric_keys = ["time"]
    for int_key in int_keys:
        if coord_dict.get(int_key):
            coord_dict[int_key] = int(coord_dict[int_key])
    for num_key in numeric_keys:
        if coord_dict.get(num_key):
            coord_dict[num_key] = float(coord_dict[num_key])


def read_file(path):
    """
    Reads a file and returns a list where each item is a line read
    """
    output_lines = []
    fopen = open(path, "r")
    for line in fopen:
        output_lines.append(line[:-1]) # leaves \n unread
    fopen.close()
    return output_lines


def clean_lines(lines):
    for i in range(len(lines)-1,-1,-1):
        line = lines[i]
        if not line.strip():
            lines.pop(i)



def range_valid_coordinates(lines, lin_range):
    range_ind = []
    count = 0
    for i in range(*lin_range):
        line = lines[i]
        if bool(is_point_time(line)):
            range_ind.append(i)
    return range_ind


def read_result_file(file_path):
    lines = read_file(file_path)
    range_num = range_valid_coordinates(lines, [0, len(lines)])
    n_data = len(range_num)

    array_shape = (n_data, 3)
    a_table = np.zeros(array_shape, dtype=float)

    i = 0
    for k in range_num:
        raw = lines[k]
        res = is_point_time(raw)
        if res:
            transform_coord_data(res)
            a_table[i, :] = [res["total"], res["border"], res["time"]]
            i += 1

    return a_table


def plot_ch_increasing_points(xLog10=False, yLog10=False, title="Performance vs Number of Points in Cloud"):
    graham_t = read_result_file(filenames[0])
    jarvis_t = read_result_file(filenames[1])

    mins = np.zeros([2,3], dtype=float)
    mins[0,:] = graham_t.min(axis=0)
    mins[1,:] = jarvis_t.min(axis=0)

    minmin = mins.min(axis=0)

    maxes = np.zeros([2,3], dtype=float)
    maxes[0,:] = graham_t.max(axis=0)
    maxes[1,:] = jarvis_t.max(axis=0)
    maxmax = maxes.max(axis=0)

    fig = plt.figure()
    #plt.gcf().subplots_adjust(bottom=0.15, top=0.8)
    ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])


    xlabel = "Puntos totales"
    ylabel = "Time[s]"

    x_g = graham_t[:,0]
    y_g = graham_t[:,2]

    x_j = jarvis_t[:,0]
    y_j = jarvis_t[:,2]

    ax_lims = np.array([minmin[2]*9/10, maxmax[2]*11/10])
    if xLog10:
        xlabel = "log10 " + xlabel
        x_g = np.log10(x_g)
        x_j = np.log10(x_j)

    if yLog10:
        ax_lims = np.log10(ax_lims)
        ylabel = "log10 " + ylabel
        y_g = np.log10(y_g)
        y_j = np.log10(y_j)
    #ax.plot(x,y, label="{} threads".format(threads))
    ax.plot(x_g,y_g, label="Graham Scan")
    ax.plot(x_j,y_j, label="Gift Wrap")


    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.legend()

    ax.set_ylim(*ax_lims)

    ax.grid(b=True)
    plt.show()
    #ax.savefig('myfile.png', bbox_inches="tight")


def plot_ch_increasing_vertices(xLog10=False, yLog10=False, title="Performance vs Number of Vertices in Convex Hull"):
    graham_t = read_result_file(filenames[2])
    jarvis_t = read_result_file(filenames[3])

    mins = np.zeros([2,3], dtype=float)
    mins[0,:] = graham_t.min(axis=0)
    mins[1,:] = jarvis_t.min(axis=0)

    minmin = mins.min(axis=0)

    maxes = np.zeros([2,3], dtype=float)
    maxes[0,:] = graham_t.max(axis=0)
    maxes[1,:] = jarvis_t.max(axis=0)
    maxmax = maxes.max(axis=0)

    fig = plt.figure()
    #plt.gcf().subplots_adjust(bottom=0.15, top=0.8)
    ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])


    xlabel = "Puntos en Hull"
    ylabel = "Time[s]"

    x_g = graham_t[:,1]
    y_g = graham_t[:,2]

    x_j = jarvis_t[:,1]
    y_j = jarvis_t[:,2]

    ax_lims = np.array([minmin[2]*9/10, maxmax[2]*11/10])
    if xLog10:
        xlabel = "log10 " + xlabel
        x_g = np.log10(x_g)
        x_j = np.log10(x_j)

    if yLog10:
        ax_lims = np.log10(ax_lims)
        ylabel = "log10 " + ylabel
        y_g = np.log10(y_g)
        y_j = np.log10(y_j)
    #ax.plot(x,y, label="{} threads".format(threads))
    ax.plot(x_g,y_g, label="Graham Scan")
    ax.plot(x_j,y_j, label="Gift Wrap")

    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.legend()

    ax.set_ylim(*ax_lims)

    ax.grid(b=True)
    plt.show()
    #ax.savefig('myfile.png', bbox_inches="tight")


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--log10", help="Shows axes in logarithmic (base 2) scale for both X and Y",
                        action="store_true")
    parser.add_argument("--xlog10", help="Shows axes in logarithmic (base 2) scale for X axis",
                        action="store_true")
    parser.add_argument("--ylog10", help="Shows axes in logarithmic (base 2) scale for Y axis",
                        action="store_true")
    parser.add_argument("--chInc", help="Plots results for performance of convex hull algorithms over increasing "
                                        "amount of points in dataset.",
                        action="store_true")
    parser.add_argument("--chVert", help="Plots results for performance of convex hull algorithms over increasing "
                                         "amount of vertices in convex hull.",
                        action="store_true")
    args = parser.parse_args()

    ch_inds = []
    if args.chInc:
        ch_inds.append(0)
    if args.chVert:
        ch_inds.append(1)
    if not ch_inds:
        print("Please, enter a valid argument. You can also stack various plots.", file=sys.stderr)
        parser.print_help(sys.stderr)
        sys.exit(1)

    xlog = args.log10 or args.xlog10
    ylog = args.log10 or args.ylog10

    funs = [plot_ch_increasing_points, plot_ch_increasing_vertices ]

    for ind in ch_inds:
        funs[ind](xLog10=xlog, yLog10=ylog)
