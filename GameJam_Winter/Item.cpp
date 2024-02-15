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
            //�A�C�e���̕\��
            DrawRotaGraph(item[i].x, item[i].y, 1.0f, 0, item[i].img, 1, 0);

            //�܂��������Ɉړ�
            item[i].y += item[i].speed;

            //��ʂ����o����폜
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
//            //�A�C�e���̕\��
//            DrawRotaGraph(item[i].x, item[i].y, 1.0f, 0, item[i].img, TRUE, FALSE);
//
//            //�܂��������Ɉړ�
//            item[i].y += item[i].speed;
//
//            //��ʂ����o����폜
//            if (item[i].y > 720) item[i].flg = FALSE;
//
//            ////�����蔻��
//            //if (HitBoxPlayer(&Player, &item[i]) == TRUE) {
//            //    item[i].flg = FALSE;
//            //    //�����A�C�e��
//            //    if (item[i].type == 0) {
//            //        Player.fuel += item[i].point;
//            //    }
//            //    //�H��A�C�e��
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
//    ////���s�������ƂɃA�C�e���o���p�^�[���𐧌䂷��
//    //if (mileage / 10 % 500 == 0) {
//    //    CreateItem();
//    //}
//
//}

int Item::CreateItem()
{
    struct ITEM item[ITEM_MAX];
    struct ITEM item00 = { 1, 0, 0, 0, -50, 50, 50, 0, 1 };
    //�A�C�e���̏����ݒ�
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

            //����
            return 1;

        }
    }
    //���s
    return 0;

}
