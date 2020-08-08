// 最終課題.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map> //mapを使用するために導入
#include <fstream>
#include <vector>
#include <iomanip> //マニピュレータを使用するために導入
using namespace std;

//Movieクラスの定義
class Movie { 
public:
    string title;
    int release = 0;
    string director;
    int satisfaction = 0;
public:
    //メンバ関数の定義
    void setTitle(const string& newTitle) { title = newTitle; }
    string getTitle() { return title; }
    void setRelease(int newRelease) { release = newRelease; }
    int getRelease() { return release; }
    void setDirector(const string& newDirector) { director = newDirector; }
    string getDirector() { return director; }
    void setSatisfaction(int newSatisfaction) { satisfaction = newSatisfaction; }
    int getSatisfaction() { return satisfaction; }
};

int main() {
    //プログラムの説明を表示するときに使用する文字（頻度の高いもの）
    string tit = "Title";
    string rel = "Release date in the US";
    string dir = "Director";
    string sat = "Satisfaction Level";

start: //入力された文字に当てはまるものがなかった場合、ここに戻ってくるためのラベル

    //以下、プログラムのタイトル
    cout << "＊＊ Sort Strings In Ascending Order For Alex ＊＊" << "\n";
    //以下、キーボードに打ち込むべき文字の説明
    cout << " If you want to put ' " << tit << " ' in order,push 't' and 'ENTER'" << "\n";
    cout << " If you want to put ' " << rel << " ' in order,push 'r' and 'ENTER'" << "\n";
    cout << " If you want to put ' " << dir << " ' in order,push 'd' and 'ENTER'" << "\n";
    cout << " If you want to put ' " << sat << " ' in order,push 's' and 'ENTER'" << "\n";
    string sort;
    cin >> sort; //標準入力から打ち込まれた文字を読み込む

    ifstream infile("movie.txt"); //テキストファイルを開く
    string Title;
    int Release;
    string Director;
    int Satisfaction;
    vector<Movie> v; //Vectorの宣言
    //mapはkeyとvalueの組
    //multimapは、keyが同じものがあっても、異なるvalueが追加される。
    //これによって、例えば監督が同じで異なる映画でもvalueを上書きしないため、表示できるようになる。
    map<string, int> list1; //タイトルを辞書順に並び替える list1
    multimap<int, int> list2; //全米公開日を早い順に並び替える list2
    multimap<string, int> list3; //監督の名前を辞書順に並び替える list3
    multimap<int, int> list4; //満足度を低い順に並び替える list4
    int i = 0;
    while (infile >> Title >> Release >> Director >> Satisfaction) {
        v.emplace_back(); //Vectorに要素を追加
        v[i].setTitle(Title);
        v[i].setRelease(Release);
        v[i].setDirector(Director);
        v[i].setSatisfaction(Satisfaction);
        list1[Title] = i; //mapのkey(Title)とvalueの追加
        list2.insert(make_pair(Release,i)); //multimapのkey(Release)とvalueの追加
        list3.insert(make_pair(Director,i)); 
        list4.insert(make_pair(Satisfaction,i)); 
        //map,multimapの要素はkeyで自動的にソートされる
        i++;
    }
    infile.close();

    static int x = 0; //staticを使うことで、xの値が初期化されずに維持される。
    static int y = 0;
    size_t size = v.size(); //Vectorのサイズを読み込む。
    //列の最大文字数を取得する。
    for (size_t i = 0; i < size; ++i) {
        size_t s = v[i].getTitle().length();
        size_t t = v[x].getTitle().length();
        size_t u = v[i].getDirector().length();
        size_t w = v[y].getDirector().length();
            if (s >= t) //「s >= t」のとき、
                x = i; //「x = i」を代入する。
            if (u >= w)
                y = i;
    }
    
    //キーボードで't'と入力された場合
    if (sort == "t") { 
        cout << "Result for sorting ' " << tit << " ' in ascending order" << "\n";
        //各列が何を表すかの説明を表示する。
        //setw()は、文字数を制限するために必要なマニピュレータで、{ ()内の数字ー１}が入力できる最大の文字数を表す。
        //今回は、列を揃える目的で使用した。
        //leftは左詰めで表示することを指す。
        cout << setw(v[x].getTitle().length() ) << left << tit  << " (" << rel << ") "
            << setw( v[y].getDirector().length() ) << left << dir << " (" << sat << ") " << "\n";
        for (const auto& p : list1) {
            //valueとvectorを対応付けて、タイトルを辞書順に表示
            //イテレータの使用
            cout << setw( v[x].getTitle().length() ) << left << v[p.second].getTitle() << " (" << setw( rel.length() ) << left <<v[p.second].getRelease() << ") "
                << setw( v[y].getDirector().length() ) << left << v[p.second].getDirector() << " (" << v[p.second].getSatisfaction() << ") " << endl;
        }
    }
    //キーボードで'r'と入力された場合
    else if (sort == "r") { 
        cout << "Result for sorting ' " << rel << " ' in ascending order" << "\n";
        //"t"が入力された場合と同じ
        cout << setw( v[x].getTitle().length() ) << left << tit << " (" << rel << ") "
            << setw( v[y].getDirector().length() ) << left << dir << " (" << sat << ") " << "\n";
        for (const auto& p : list2) {
            //valueとvectorを対応付けて、全米公開日を早い順に表示
            cout << setw( v[x].getTitle().length() ) << left << v[p.second].getTitle() << " (" << setw(rel.length()) << left << v[p.second].getRelease() << ") "
                << setw( v[y].getDirector().length() ) << left << v[p.second].getDirector() << " (" << v[p.second].getSatisfaction() << ") " << endl;
        }
    }
    //キーボードで'd'と入力された場合
    else if (sort == "d") { 
        cout << "Result for sorting ' " << dir << " ' in ascending order" << "\n";
        //"t"が入力された場合と同じ
        cout << setw( v[x].getTitle().length() ) << left << tit << " (" << rel << ") "
            << setw( v[y].getDirector().length() ) << left << dir << " (" << sat << ") " << "\n";
        for (const auto& p : list3) {
            //valueとvectorを対応付けて、監督の名前を辞書順に表示
            cout << setw( v[x].getTitle().length() ) << left << v[p.second].getTitle() << " (" << setw(rel.length()) << left << v[p.second].getRelease() << ") "
                << setw( v[y].getDirector().length() ) << left << v[p.second].getDirector() << " (" << v[p.second].getSatisfaction() << ") " << endl;
        }
    }
    //キーボードで's'と入力された場合
    else if (sort == "s") { 
        cout << "Result for sorting ' " << sat << " ' in ascending order" << "\n";
        //"t"が入力された場合と同じ
        cout << setw( v[x].getTitle().length() ) << left << tit << " (" << rel << ") "
            << setw( v[y].getDirector().length() ) << left << dir << " (" << sat << ") " << "\n";
        for (const auto& p : list4) {
            //valueとvectorを対応付けて、満足度を低い順に表示
            cout << setw( v[x].getTitle().length() ) << left << v[p.second].getTitle() << " (" << setw(rel.length()) << left << v[p.second].getRelease() << ") "
                << setw( v[y].getDirector().length() ) << left << v[p.second].getDirector() << " (" << v[p.second].getSatisfaction() << ") " << endl;
        }
    }
    //キーボードで入力された文字が上のどれにも当てはまらない場合
    else {
        //エラーメッセージの表示
        cout << "　　　＃ERROR＃　　　" << "\n"
            << " You pushed '" << sort << "' !" << "\n"
            << " PUSH 't','r','d',or's'." << "\n" << "\n";
        goto start; //ラベルのstartの位置まで戻る
    }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
