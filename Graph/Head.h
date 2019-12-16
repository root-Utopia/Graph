#define DEBUG
#define isCtrl(c)     ((c >= 0) && (c < 33)) && ((c != '\n') && (c != '\t'))
#define ABS(x)        (((x) > 0) ? (x) : ((x) < 0) ? ((x)*(-1)) : (x))
#define MAX(x, y)     (((x) > (y)) ? (true) : (false))
#define MIN(x, y)     (!MAX((x), (y)))
#define SQUARE(x)     (x)*(x)
#define CUBE(x)       SQUARE((x)) * (x)
#define INF           100000
#define PI            3.1415926536
#define ESC           27
#define NUMADD        43
#define NUMSUB        45
#define u			  unsigned
#define ll            long long
#define ull			  u ll
#define uint          u int
#define ush			  u short
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <fstream>
#include <cstdio>
#include "cctype"
#include "conio.h"
#include <cstdlib>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <forward_list>
#include <vector>
#include <cmath>
#include <array>
#include <iterator>
#include <search.h>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <utility>
#include <limits.h>
using namespace std;