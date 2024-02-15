#include "item.h"
#include"DxLib.h"
#include"Player.h"

Item::Item()
{
	item_image[0] = LoadGraph("Resource / images / barrier.png");
	item_image[1] = LoadGraph("Resource / images / Helth.bmp");
	item_image[2] = LoadGraph("Resource / images /supana.bmp");

}

Item::~Item()
{
}

void Item::Update()
{

}

void Item::Draw() const
{
    struct ITEM item[ITEM_MAX];
    struct ITEM item00 = { 1, 0, 0, 0, -50, 50, 50, 0, 1 };

    for (int i = 0; i < ITEM_MAX; i++) {
        if (item[i].flg == 1) {
            //アイテムの表示
            DrawRotaGraph(item[i].x, item[i].y, 1.0f, 0, item[i].img, 1, 0);

            //まっすぐ下に移動
            item[i].y += item[i].speed;

            //画面が羅出たら削除
            if (item[i].y > 720) item[i].flg = 0;


        }
        //DrawFormatString(1110, 400, GetColor(0, 0, 0), "%d", ITEM_MAX);
    }

}

//void Item::ItemControl()
//{
//    struct ITEM item[ITEM_MAX];
//    //struct ITEM item00 = { TRUE, 0, 0, 0, -50, 50, 50, 0, 1 };
//
//    for (int i = 0; i < ITEM_MAX; i++) {
//        if (item[i].flg == TRUE) {
//            //アイテムの表示
//            DrawRotaGraph(item[i].x, item[i].y, 1.0f, 0, item[i].img, TRUE, FALSE);
//
//            //まっすぐ下に移動
//            item[i].y += item[i].speed;
//
//            //画面が羅出たら削除
//            if (item[i].y > 720) item[i].flg = FALSE;
//
//            ////当たり判定
//            //if (HitBoxPlayer(&Player, &item[i]) == TRUE) {
//            //    item[i].flg = FALSE;
//            //    //給油アイテム
//            //    if (item[i].type == 0) {
//            //        Player.fuel += item[i].point;
//            //    }
//            //    //工具アイテム
//            //    if (item[i].type == 1) {
//            //        Player.hp += item[i].point;
//            //        if (Player.hp > PLAYER_HP)Player.hp = PLAYER_HP;
//            //    }
//
//            //}
//
//        }
//        DrawFormatString(1110, 400, GetColor(0, 0, 0), "%d",ITEM_MAX);
//    }
//
//    ////走行距離ごとにアイテム出現パターンを制御する
//    //if (mileage / 10 % 500 == 0) {
//    //    CreateItem();
//    //}
//
//}

int Item::CreateItem()
{
    struct ITEM item[ITEM_MAX];
    struct ITEM item00 = { 1, 0, 0, 0, -50, 50, 50, 0, 1 };
    //アイテムの初期設定
    for (int i = 0; i < ITEM_MAX; i++) {
        item[i].flg = FALSE;
    }

    for (int i = 0; i < ITEM_MAX; i++) {
        if (item[i].flg == 0) {
            item[i] = item00;
            item[i].type = GetRand(1);
            item[i].img = item_image[item[i].type];
            item[i].x = GetRand(4) * 105 + 40;
            item[i].speed = 1 + item[i].type * 3;
            //if (item[i].type == 0)item[i].point = 500;
            //if (item[i].type == 1)item[i].point = 50;

            //成功
            return 1;

        }
    }
    //失敗
    return 0;

}
