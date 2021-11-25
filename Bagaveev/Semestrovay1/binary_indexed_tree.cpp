#include <iostream>
#include <windows.h> // для отображения кириллицы
using namespace std;

int f(int x){ // зануляет блок младших единиц
    return x&(x+1);
}

int g(int x){   // заединичивает младший ноль
    return x|(x+1);
}

int Sum(int fw[], int i) {
    int res = 0;
    for (; i >= 0; i = f(i)-1){
        res += fw[i];
    }
    /* i -> f(i)-1, при этом младший ноль становится единицей и что-то еще в более старших разрядов, но это не существенно
     * число шагов не превышает число бит в i т.е. <= log(n)
     * когда берем f(i) мы сдвигаем индекс на тот отрезок который мы посчитали, а -1 нужен для, того чтобы посчитать следующий отрезок не включенный в предыдущий
     */
    return res;
}

int getSum(int fw[], int l, int r) {
    return Sum(fw, r) - Sum(fw, l - 1);
    // берем сумму на префиксе до r, вычтем на префиксе l-1 и получим искомую сумму
}

void update(int fw[], int n, int i, int newVal) {
    /*
     * итераций столько сколько нулей в исходном числе
     * т.к в двоичной записи log(n) бит, то и итераций будет log(n)
     * Таким образом update и Sum работают за log(n)
     */
    for (; i < n; i = g(i)){
        fw[i] += newVal;
    }
    /*
     * При изменении одного элемента, нам надо изменить все суммы в которые он входит
     * Представим себе, что a[pos] увеличивается на val.
     * Тогда меняются те fw[i] в отрезке которых есть pos то есть, которые удовлетворяют условию f(i) <= pos <= i
     * Т.к для каждого i число fw[i] это сумма на отрезке с f(i) до i, соответственно это сумма может поменяться, если в него попало число a[pos]
     * f(i) [       ] 00000
     * pos  [       ] 0... что угодно
     * i    [       ] 01111
     * Функции g(x) заединичает младший ноль, таким образом мы проходимся по все I-ым элементам и изменяем их
     */
}

int *build(int a[], int n) {
    int *fw = new int[n+1];
    for (int i = 0; i <= n; ++i){
        fw[i] = 0;
    }
    /*
     * Для того чтобы построить дерево достаточно, взять нулевой массив равный размеру исходного
     * и N раз вызвать операцию изменения элемента
     */
    for (int i = 0; i < n; ++i)
        update(fw, n, i, a[i]);

    return fw;
}

int main(){
    SetConsoleOutputCP(CP_UTF8); // для отображения кириллицы
    int n;
    cout << "Введите размер массива:";
    cin >> n;
    int* a = new int[n];
    cout << "Введите элемента массива:";
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    a = build(a,n); // строим дерево Фенвика
    cout << endl;
    cout << "Количество запросов:";
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i){ // обработка запросов
        int l,r;
        cout << "Введите левую и правую границу отрезка:";
        cin >> l >> r;
        cout << "Сумма на отрезке равна:" << getSum(a,l-1,r-1) << endl;
        cout << endl;
    }
    delete [] a;
    return 0;
}


