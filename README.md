# competitive-library

自分用の競技プログラミングライブラリです。

## 使い方

パスにincludeディレクトリを追加すると使えます。

```
g++ -std=c++23 -Icompetitive-library/include main.cpp
```

## コンテンツ

- ac-library
  - original: [AC Library](https://github.com/atcoder/ac-library)のライブラリ部分
  - custom: C++20を前提とし並列コンパイルに対応させた改造品
- expander
  - このライブラリのヘッダをcppファイルに展開するアプリ
- include
  - ライブラリの中身
- unittest
  - 明示的にテストを記述した単体テスト
- random_test
  - テスト内容を自動生成させたテスト

## ライセンス

- ac-library下を除くコードはMITライセンスで提供されるものとします。
- ac-library下のコードはCC0で提供されるものとします。
