#include "herojump.h"
#include "ui_herojump.h"
#include <QDebug>
#include <QKeyEvent>
#include <QString>
#include <QTextStream>
#include <QFontDatabase>

static int hero_jump;
static int start_Hero;
static QFile file(":/ranking/ranking.txt");

HeroJump::HeroJump(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeroJump)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    this->setFixedSize(QSize(928, 563));

    EventFilter* key = new EventFilter();
    this->installEventFilter(key);

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QFontDatabase::addApplicationFont(":/font/Font/old-english.ttf");
    QFont font = QFont("Old English Text MT", 16, 1, 0);
    ui->label_Score->setFont(font);
    ui->pushButton_comboBox_ports->setFont(font);

    QPixmap start_button(":/gui/GUI/GUI-button-start.png");
    QIcon ButtonIcon_start(start_button);
    ui->pushButton_start->setIcon(ButtonIcon_start);
    ui->pushButton_start->setIconSize(start_button.rect().size());
    ui->pushButton_start->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QPixmap options_button(":/gui/GUI/GUI-button-options.png");
    QIcon ButtonIcon_options(options_button);
    ui->pushButton_options->setIcon(ButtonIcon_options);
    ui->pushButton_options->setIconSize(options_button.rect().size());
    ui->pushButton_options->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QPixmap exit_button(":/gui/GUI/GUI-button-exit.png");
    QIcon ButtonIcon_exit(exit_button);
    ui->pushButton_exit->setIcon(ButtonIcon_exit);
    ui->pushButton_exit->setIconSize(exit_button.rect().size());
    ui->pushButton_exit->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QPixmap open_button(":/gui/GUI/GUI-button-open.png");
    QIcon ButtonIcon_open(open_button);
    ui->pushButton_open->setIcon(ButtonIcon_open);
    ui->pushButton_open->setIconSize(open_button.rect().size());
    ui->pushButton_open->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QPixmap score_button(":/gui/GUI/GUI-button-score.png");
    QIcon ButtonIcon_score(score_button);
    ui->pushButton_score->setIcon(ButtonIcon_score);
    ui->pushButton_score->setIconSize(score_button.rect().size());
    ui->pushButton_score->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    //QPixmap combo_box_button(":/gui/GUI/GUI-menu.png");
    //QIcon ComboBoxIcon_porta(combo_box_button);
    //
    //
    //

    ui->pushButton_label_menu->setPixmap(QPixmap(QString(":/gui/GUI/GUI-menu.png")));

    ui->label_Environment_layer_00_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0000_9.png")));
    ui->label_Environment_layer_00_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0000_9.png")));

    ui->label_Environment_layer_01_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0001_8.png")));
    ui->label_Environment_layer_01_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0001_8.png")));

    ui->label_Environment_layer_02_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0002_7.png")));
    ui->label_Environment_layer_02_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0002_7.png")));

    ui->label_Environment_layer_03_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0003_6.png")));
    ui->label_Environment_layer_03_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0003_6.png")));

    ui->label_Environment_layer_04_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0004_Light.png")));
    ui->label_Environment_layer_04_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0004_Light.png")));

    ui->label_Environment_layer_05_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0005_5.png")));
    ui->label_Environment_layer_05_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0005_5.png")));

    ui->label_Environment_layer_06_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0006_4.png")));
    ui->label_Environment_layer_06_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0006_4.png")));

    ui->label_Environment_layer_07_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0007_Light.png")));
    ui->label_Environment_layer_07_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0007_Light.png")));

    ui->label_Environment_layer_08_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0008_3.png")));
    ui->label_Environment_layer_08_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0008_3.png")));

    ui->label_Environment_layer_09_I->setPixmap(QPixmap(QString(":/background/Background/Layer_0009_2.png")));
    ui->label_Environment_layer_09_O->setPixmap(QPixmap(QString(":/background/Background/Layer_0009_2.png")));

    ui->label_Environment_layer_10->setPixmap(QPixmap(QString(":/background/Background/Layer_0010_1.png")));

    ui->pushButton_comboBox_ports->setDisabled(true);
    ui->pushButton_comboBox_ports->setHidden(true);

    ui->pushButton_open->setDisabled(true);
    ui->pushButton_open->setHidden(true);

    ui->pushButton_score->setDisabled(true);
    ui->pushButton_score->setHidden(true);
}

HeroJump::~HeroJump()
{
    delete ui;

    if(serial.isOpen())
            serial.close();
}

void HeroJump::on_pushButton_start_clicked()
{
    death_flag = 0;
    contDeath = 0;
    score = 0;

    start_Hero = 465;
    hero_jump = 0;

    ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 285, 285));
    ui->label_Hero->setGeometry(QRect(hero_x, start_Hero, 36, 47));

    ui->label_Enemy_Ogre_Shockwave->setHidden(true);
    ui->pushButton_label_menu->setHidden(true);

    ui->pushButton_start->setDisabled(true);
    ui->pushButton_start->setHidden(true);

    ui->pushButton_options->setDisabled(true);
    ui->pushButton_options->setHidden(true);

    ui->pushButton_exit->setDisabled(true);
    ui->pushButton_exit->setHidden(true);

    ui->pushButton_comboBox_ports->setDisabled(true);
    ui->pushButton_comboBox_ports->setHidden(true);

    ui->pushButton_open->setDisabled(true);
    ui->pushButton_open->setHidden(true);

    ui->pushButton_score->setDisabled(true);
    ui->pushButton_score->setHidden(true);

    timer_run_game = new QTimer(this);
    connect(timer_run_game, SIGNAL(timeout()), this, SLOT(run_Game()));
    timer_run_game->start(30);

    timer_animation_hero = new QTimer(this);
    connect(timer_animation_hero, SIGNAL(timeout()), this, SLOT(run_Animation()));
    timer_animation_hero->start(105);

    timer_animation_enemy = new QTimer(this);
    connect(timer_animation_enemy, SIGNAL(timeout()), this, SLOT(run_Animation_special()));
    timer_animation_enemy->start(200);
}

void HeroJump::on_pushButton_options_clicked()
{
    ui->pushButton_start->setDisabled(true);
    ui->pushButton_start->setHidden(true);

    ui->pushButton_options->setDisabled(true);
    ui->pushButton_options->setHidden(true);

    ui->pushButton_comboBox_ports->setEnabled(true);
    ui->pushButton_comboBox_ports->setVisible(true);

    ui->pushButton_open->setVisible(true);

    exit_game++;

    open_Port();
}

void HeroJump::open_Port()
{
    int ports=0;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->pushButton_comboBox_ports->addItem(info.portName());
        ports++;
    }
    if(ports > 0)
        ui->pushButton_open->setEnabled(true);
    else
        ui->pushButton_open->setEnabled(false);
}

void HeroJump::on_pushButton_open_clicked()
{
    serial.setPortName(nome);
    serial.setBaudRate(9600);

    if(serial.open(QIODevice::ReadWrite))
        msg.setText("Porta aberta com sucesso!");
    else
        msg.setText("Porta não pode ser aberta!");

    msg.exec();

    ui->pushButton_start->setEnabled(true);
    ui->pushButton_start->setVisible(true);

    ui->pushButton_options->setEnabled(true);
    ui->pushButton_options->setVisible(true);

    ui->pushButton_exit->setEnabled(true);
    ui->pushButton_exit->setVisible(true);

    ui->pushButton_comboBox_ports->setDisabled(true);
    ui->pushButton_comboBox_ports->setHidden(true);

    ui->pushButton_open->setDisabled(true);
    ui->pushButton_open->setHidden(true);
}

void HeroJump::on_pushButton_exit_clicked()
{
    if(exit_game == 0)
    {
        if(serial.isOpen())
                serial.close();
        exit(1);
    }
    if(exit_game == 1)
    {
        ui->pushButton_start->setEnabled(true);
        ui->pushButton_start->setVisible(true);

        ui->pushButton_options->setEnabled(true);
        ui->pushButton_options->setVisible(true);

        ui->pushButton_comboBox_ports->setDisabled(true);
        ui->pushButton_comboBox_ports->setHidden(true);

        ui->pushButton_open->setDisabled(true);
        ui->pushButton_open->setHidden(true);

        exit_game = 0;
    }
}

void HeroJump::on_pushButton_comboBox_ports_currentIndexChanged(const QString &arg1)
{
    nome = arg1;
}

void HeroJump::on_pushButton_score_clicked()
{
    QString scores;
    QString score_List(":/ranking/ranking.txt");
    QFile score(score_List);

    if(score.open(QIODevice::ReadOnly))
    {
        QTextStream in(&score);
        while(!in.atEnd())
            scores += in.readLine();
    }

    msg.setText(scores);
    score.close();
}

void HeroJump::run_Menu()
{
    ui->pushButton_label_menu->setVisible(true);

    ui->pushButton_start->setEnabled(true);
    ui->pushButton_start->setVisible(true);

    ui->pushButton_score->setEnabled(true);
    ui->pushButton_score->setVisible(true);

    ui->pushButton_exit->setEnabled(true);
    ui->pushButton_exit->setVisible(true);
}

void HeroJump::run_Game()
{
    //qDebug() << "boss_defeat" << boss_defeat;
    //qDebug() << "hero_x" << hero_x;

    run_Enemy();
    run_Collision();
    run_Background();
    run_Hero_boss();

    if(hero_jump != 0)
        run_jump_Hero();
}

void HeroJump::run_Background()
{
    ui->label_Environment_layer_00_I->setGeometry(QRect(start_background_00_I, -230, 928, 793));
    ui->label_Environment_layer_00_O->setGeometry(QRect(start_background_00_O, -230, 928, 793));

    ui->label_Environment_layer_01_I->setGeometry(QRect(start_background_01_I, -230, 928, 793));
    ui->label_Environment_layer_01_O->setGeometry(QRect(start_background_01_O, -230, 928, 793));

    ui->label_Environment_layer_02_I->setGeometry(QRect(start_background_02_I, -230, 928, 793));
    ui->label_Environment_layer_02_O->setGeometry(QRect(start_background_02_O, -230, 928, 793));

    ui->label_Environment_layer_03_I->setGeometry(QRect(start_background_03_I, -230, 928, 793));
    ui->label_Environment_layer_03_O->setGeometry(QRect(start_background_03_O, -230, 928, 793));

    ui->label_Environment_layer_04_I->setGeometry(QRect(start_background_04_I, -230, 928, 793));
    ui->label_Environment_layer_04_O->setGeometry(QRect(start_background_04_O, -230, 928, 793));

    ui->label_Environment_layer_05_I->setGeometry(QRect(start_background_05_I, -230, 928, 793));
    ui->label_Environment_layer_05_O->setGeometry(QRect(start_background_05_O, -230, 928, 793));

    ui->label_Environment_layer_06_I->setGeometry(QRect(start_background_06_I, -230, 928, 793));
    ui->label_Environment_layer_06_O->setGeometry(QRect(start_background_06_O, -230, 928, 793));

    ui->label_Environment_layer_07_I->setGeometry(QRect(start_background_07_I, -230, 928, 793));
    ui->label_Environment_layer_07_O->setGeometry(QRect(start_background_07_O, -230, 928, 793));

    ui->label_Environment_layer_08_I->setGeometry(QRect(start_background_08_I, -230, 928, 793));
    ui->label_Environment_layer_08_O->setGeometry(QRect(start_background_08_O, -230, 928, 793));

    ui->label_Environment_layer_09_I->setGeometry(QRect(start_background_09_I, -230, 928, 793));
    ui->label_Environment_layer_09_O->setGeometry(QRect(start_background_09_O, -230, 928, 793));

    start_background_00_I -= 4;
    start_background_00_O -= 4;

    start_background_01_I -= 4;
    start_background_01_O -= 4;

    start_background_02_I -= 4;
    start_background_02_O -= 4;

    start_background_03_I -= 4;
    start_background_03_O -= 4;

    start_background_04_I -= 4;
    start_background_04_O -= 4;

    start_background_05_I -= 2;
    start_background_05_O -= 2;

    start_background_06_I -= 2;
    start_background_06_O -= 2;

    start_background_07_I -= 2;
    start_background_07_O -= 2;

    start_background_08_I -= 1;
    start_background_08_O -= 1;

    start_background_09_I -= 1;
    start_background_09_O -= 1;

    if(start_background_00_I == -928)
        start_background_00_I = 928;
    if(start_background_00_O == -928)
        start_background_00_O = 928;

    if(start_background_01_I == -928)
        start_background_01_I = 928;
    if(start_background_01_O == -928)
        start_background_01_O = 928;

    if(start_background_02_I == -928)
        start_background_02_I = 928;
    if(start_background_02_O == -928)
        start_background_02_O = 928;

    if(start_background_03_I == -928)
        start_background_03_I = 928;
    if(start_background_03_O == -928)
        start_background_03_O = 928;

    if(start_background_04_I == -928)
        start_background_04_I = 928;
    if(start_background_04_O == -928)
        start_background_04_O = 928;

    if(start_background_05_I == -928)
        start_background_05_I = 928;
    if(start_background_05_O == -928)
        start_background_05_O = 928;

    if(start_background_06_I == -928)
        start_background_06_I = 928;
    if(start_background_06_O == -928)
        start_background_06_O = 928;

    if(start_background_07_I == -928)
        start_background_07_I = 928;
    if(start_background_07_O == -928)
        start_background_07_O = 928;

    if(start_background_08_I == -928)
        start_background_08_I = 928;
    if(start_background_08_O == -928)
        start_background_08_O = 928;

    if(start_background_09_I == -928)
        start_background_09_I = 928;
    if(start_background_09_O == -928)
        start_background_09_O = 928;
}

void HeroJump::run_Score()
{
    ui->label_Score->setText(QString::number(score));
    score++;
}

void HeroJump::run_Hero_boss()
{
    //qDebug() << "hero_x" << hero_x;
    //qDebug() << "trigger" << boss_trigger;

    if(boss_trigger == 2 && start_Enemy_oculothorax == 1000 && start_Enemy_slime == 1000)
    {
        ui->label_Hero->setGeometry(QRect(hero_x, start_Hero, 36, 47));
        hero_x += hero_run;

        if(hero_x == 840)
            hero_run = 0;
    }
    if(boss_defeat >= 1)
    {
        ui->label_Hero->setGeometry(QRect(hero_x, start_Hero, 36, 47));
        hero_x -= hero_run;

        if(hero_x == 50)
        {
            hero_run = 0;
            boss_defeat = 0;
            stop_slime = 0;
            stop_oculothorax = 0;
            start_Enemy_slime = 1000;
            start_Enemy_oculothorax = 2000;
        }
    }
}

void HeroJump::run_jump_Hero()
{
    //qDebug() << "hero_jump" << hero_jump;
    //qDebug() << "start_Hero" << start_Hero;

    start_Hero += hero_jump;
    hero_jump += 1;

    if(start_Hero == 387)
        hero_jump = 1;
    if(start_Hero == 465)
        hero_jump = 0;

    ui->label_Hero->setGeometry(QRect(hero_x, start_Hero, 36, 47));
}

void HeroJump::run_Animation()
{
    run_Animation_hero();
    run_Animation_enemy();
    run_Animation_enemy_shockwave();
}

void HeroJump::run_Animation_special()
{
    if(start_Hero != 465)
        run_Animation_jump();
}

void HeroJump::run_Animation_hero()
{
    if(contRun_hero == 6)
        contRun_hero = 0;

    if(death_flag == 1)
        run_Animation_death();

    else if(hero_jump == 0)
    {
        ui->label_Hero->setPixmap(QPixmap(QString(":/hero/Hero/adventurer-run-0"+QString::number(contRun_hero)+".png")));
        run_Score();
    }
    else if(hero_jump != 0)  
        run_Score();

    contRun_hero++;
}

void HeroJump::run_Animation_jump()
{
    if(contJump_down == 2)
        contJump_down = 0;

    if(hero_jump < 0)
        ui->label_Hero->setPixmap(QPixmap(QString(":/hero/Hero/adventurer-jump-00.png")));

    if(hero_jump > 0)
    {
        ui->label_Hero->setPixmap(QPixmap(QString(":/hero/Hero/adventurer-fall-0"+QString::number(contJump_down)+".png")));
        contJump_down++;
    }
}

void HeroJump::run_Animation_death()
{
    if(contDeath == 7)
    {
        ui->label_Hero->setPixmap(QPixmap(QString(":/hero/Hero/adventurer-die-06.png")));

        timer_animation_hero->stop();
        timer_animation_hero->deleteLater();

        start_Enemy_slime = 1000;
        start_Enemy_oculothorax = 2000;
    }
    if(contDeath < 7)
    {
        ui->label_Hero->setPixmap(QPixmap(QString(":/hero/Hero/adventurer-die-0"+QString::number(contDeath)+".png")));
        contDeath++;
    }
}

void HeroJump::run_Animation_enemy()
{
    if(death_flag == 0)
    {
        if(contRun_slime == 4)
            contRun_slime = 0;
        if(contRun_oculothorax == 4)
            contRun_oculothorax = 0;

        ui->label_Enemy_Slime->setPixmap(QPixmap(QString(":/enemy/Enemy/Slime/slime-move-0"+QString::number(contRun_slime)+".png")));
        ui->label_Enemy_Oculothorax->setPixmap(QPixmap(QString(":/enemy/Enemy/Oculothorax/oculothorax-move-0"+QString::number(contRun_oculothorax)+".png")));

        contRun_slime++;
        contRun_oculothorax++;

        if(boss_attack < 60)
        {
            ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 285, 285));

            if(contRun_ogre == 6)
                contRun_ogre = 0;

            ui->label_Enemy_Ogre_Boss->setPixmap(QPixmap(QString(":/enemy/Enemy/Ogre/ogre-move-0"+QString::number(contRun_ogre)+".png")));

            contRun_ogre++;
        }

        run_Enemy_ogre_boss_attack();
    }

    else if(death_flag == 1)
    {
        if(start_Enemy_slime <= 90 && start_Enemy_slime >= 0)
            run_Enemy_slime_attack();
        if(start_Enemy_oculothorax <= 90 && start_Enemy_oculothorax >= 0)
            run_Enemy_oculothorax_attack();
    }
}

void HeroJump::run_Animation_enemy_shockwave()
{
    if(flag_shockwave >= 1)
    {
        if(contRun_shockwave == 10)
            contRun_shockwave = 0;

        ui->label_Enemy_Ogre_Shockwave->setPixmap(QPixmap(QString(":/enemy/Enemy/Ogre/ogre-shockwave-0"+QString::number(contRun_shockwave)+".png")));

        contRun_shockwave++;
    }
}

void HeroJump::run_Enemy()
{
    run_Enemy_slime();
    run_Enemy_oculothorax();
    run_Enemy_ogre_boss();
}

void HeroJump::run_Enemy_slime()
{
    if(stop_slime == 0)
    {
        start_Enemy_slime -= mov_Enemy;

        if (start_Enemy_slime <= -1000)
        {
            start_Enemy_slime = 1000;

            if(score >= score_trigger && score <= (score_trigger + 100))
            {
                stop_slime++;
                boss_trigger++;

                hero_run = 5;
            }
        }
        ui->label_Enemy_Slime->setGeometry(QRect(start_Enemy_slime, 489, 55, 23));
    }
}

void HeroJump::run_Enemy_oculothorax()
{
    if(stop_oculothorax == 0)
    {
        start_Enemy_oculothorax -= mov_Enemy;

        if (start_Enemy_oculothorax < -1000)
        {
            start_Enemy_oculothorax = 1000;

            if(score >= score_trigger && score <= (score_trigger + 100))
            {
                stop_oculothorax++;
                boss_trigger++;

                boss_attack_flag = 0;

                hero_run = 5;
            }
        }
        ui->label_Enemy_Oculothorax->setGeometry(QRect(start_Enemy_oculothorax, 475, 55, 32));
    }
}

void HeroJump::run_Enemy_ogre_boss()
{
   if(start_Enemy_ogre != 50 && boss_trigger == 2 && hero_x == 840 && boss_defeat == 0)
   {
        start_Enemy_ogre += (mov_Enemy - 5);
        ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 285, 285));
   }

   else if(start_Enemy_ogre != -290 && boss_trigger == 0 && boss_defeat == 1)
   {
        start_Enemy_ogre -= (mov_Enemy - 5);
        ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 285, 285));

        if(start_Enemy_ogre == -290)
        {
            score_trigger += 680;

            boss_defeat = 1;
        }
   }
}

void HeroJump::run_Enemy_slime_attack()
{
    qDebug() << "contAttack_slime" << contAttack_slime;

    ui->label_Enemy_Slime->setGeometry(QRect(start_Enemy_slime, 473, 55, 39));

    if(contAttack_slime == 5)
    {
        contAttack_slime = 0;

        timer_animation_enemy->stop();
        timer_animation_enemy->deleteLater();

        run_Menu();
    }

    ui->label_Enemy_Slime->setPixmap(QPixmap(QString(":/enemy/Enemy/Slime/slime-attack-0"+QString::number(contAttack_slime)+".png")));

    contAttack_slime++;
}

void HeroJump::run_Enemy_oculothorax_attack()
{
    qDebug() << "contAttack_oculothorax" << contAttack_oculothorax;

    ui->label_Enemy_Oculothorax->setGeometry(QRect(start_Enemy_oculothorax, 457, 55, 45));

    if(contAttack_oculothorax >= 6)
    {
        contAttack_oculothorax = 0;

        timer_animation_enemy->stop();
        timer_animation_enemy->deleteLater();

        run_Menu();
    }

    ui->label_Enemy_Oculothorax->setPixmap(QPixmap(QString(":/enemy/Enemy/Oculothorax/oculothorax-attack-0"+QString::number(contAttack_oculothorax)+".png")));

    contAttack_oculothorax++;
}

void HeroJump::run_Enemy_ogre_boss_attack()
{
    if(contAttack_ogre == 3)
        flag_shockwave++;

    if(flag_shockwave >= 1)
    {
        ui->label_Enemy_Ogre_Shockwave->setVisible(true);
        run_Enemy_shockwave();
    }

    if(boss_trigger == 2)
    {
        //qDebug() << "boss_attack" << boss_attack;
        //qDebug() << "boss_attack_flag" << boss_attack_flag;

        if(start_Enemy_ogre == 50)
            boss_attack++;

        if(boss_attack_flag == 3)
        {
            //qDebug() << "boss_defeat" << boss_defeat;
            //qDebug() << "boss_trigger" << boss_trigger;

            boss_defeat++;
            boss_trigger = 0;
        }

        if(boss_attack >= 60 && boss_defeat == 0)
        {
            ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 400, 285));

            if(contAttack_ogre == 7)
            {
                contAttack_ogre = 0;
                ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 285, 285));

                boss_attack = 0;
                boss_attack_flag++;
            }

            ui->label_Enemy_Ogre_Boss->setPixmap(QPixmap(QString(":/enemy/Enemy/Ogre/ogre-attack-0"+QString::number(contAttack_ogre)+".png")));

            contAttack_ogre++;
        }
    }
}

void HeroJump::run_Enemy_shockwave()
{
    //qDebug() << "shockwave" << start_Enemy_ogre_shockwave;
    //qDebug() << "restart_hero" << restart_hero;
    //qDebug() << "hero_run" << hero_run;

    start_Enemy_ogre_shockwave += (mov_Enemy + 5);

    if (start_Enemy_ogre_shockwave > 1000)
    {
        ui->label_Enemy_Ogre_Shockwave->setHidden(true);
        start_Enemy_ogre_shockwave = 350;

        flag_shockwave = 0;

        restart_hero++;
        if(restart_hero >= 3)
        {
            hero_run = 5;
            restart_hero = 0;
        }
    }

    ui->label_Enemy_Ogre_Shockwave->setGeometry(QRect(start_Enemy_ogre_shockwave, 471, 33, 41));
}

void HeroJump::run_Enemy_kill()
{
    timer_run_game->stop();
    timer_run_game->deleteLater();

    death_flag++;

    QTextStream stream(&file);
    stream << "" +QString::number(score) << endl;
}

void HeroJump::run_Collision()
{
        run_Collision_Enemy_slime();
        run_Collision_Enemy_oculothorax();
        run_Collision_Enemy_ogre_shockwave();
}

void HeroJump::run_Collision_Enemy_slime()
{
    if(start_Enemy_slime == 86 && start_Hero > 435)
        run_Enemy_kill();

    else if(start_Enemy_slime <= 86 && start_Enemy_slime >= 50 && start_Hero > 435)
        run_Enemy_kill();

    else if(start_Enemy_slime <= 50 && start_Enemy_slime >= 0 && start_Hero > 435)
        run_Enemy_kill();
}

void HeroJump::run_Collision_Enemy_oculothorax()
{
    if(start_Enemy_oculothorax == 86 && start_Hero > 435)
        run_Enemy_kill();

    else if(start_Enemy_oculothorax <= 86 && start_Enemy_oculothorax >= 50 && start_Hero > 435)
        run_Enemy_kill();

    else if(start_Enemy_oculothorax <= 50 && start_Enemy_oculothorax >= 0 && start_Hero > 435)
        run_Enemy_kill();
}

void HeroJump::run_Collision_Enemy_ogre_shockwave()
{
    if(start_Enemy_ogre_shockwave >= 809 && start_Enemy_ogre_shockwave <= 830 && start_Hero > 435)
    {
        run_Enemy_kill();

        if(death_flag == 1)
        {
            timer_animation_enemy->stop();
            timer_animation_enemy->deleteLater();

            ui->label_Enemy_Ogre_Shockwave->setHidden(true);

            start_Enemy_ogre_shockwave = 350;
            ui->label_Enemy_Ogre_Shockwave->setGeometry(QRect(start_Enemy_ogre_shockwave, 471, 33, 41));

            start_Enemy_ogre = -290;
            ui->label_Enemy_Ogre_Boss->setGeometry(QRect(start_Enemy_ogre, 227, 285, 285));

            run_Menu();
        }
    }
}

void HeroJump::run_Control()
{
    if(serial.isOpen() && start_Hero == 465)
        {
            QString read = serial.readAll();

            if(read == "\u0001")
                hero_jump = -12;
        }
}

bool EventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ((key->key() == Qt::Key_W))
        {
            if(start_Hero == 465)
                hero_jump = -12;
            return true;
        }
        else
            return QObject::eventFilter(obj, event);
        return true;
    }
    return false;
}
