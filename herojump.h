#ifndef HEROJUMP_H
#define HEROJUMP_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QtSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class HeroJump;
}

class HeroJump : public QWidget
{
    Q_OBJECT

public:
    explicit HeroJump(QWidget *parent = nullptr);
    ~HeroJump();

    int stop_slime = 0, stop_oculothorax = 0, boss_trigger = 0, boss_defeat = 0, boss_attack = 0, boss_attack_flag = 0;
    int contEnemy = 0, flag_shockwave = 0, restart_hero = 0;
    int mov_Enemy = 10, start_Enemy_slime = 1000, start_Enemy_oculothorax = 2000, start_Enemy_ogre = -290, start_Enemy_ogre_shockwave = 350;
    int start_background_00_I = 0, start_background_00_O = 928, start_background_01_I = 0, start_background_01_O = 928, start_background_02_I = 0, start_background_02_O = 928;
    int start_background_03_I = 0, start_background_03_O = 928, start_background_04_I = 0, start_background_04_O = 928, start_background_05_I = 0, start_background_05_O = 928;
    int start_background_06_I = 0, start_background_06_O = 928, start_background_07_I = 0, start_background_07_O = 928, start_background_08_I = 0, start_background_08_O = 928;
    int start_background_09_I = 0, start_background_09_O = 928;
    int contRun_hero = 0, contRun_slime = 0, contRun_oculothorax = 0, contRun_ogre = 0, contRun_shockwave = 0,contAttack_slime = 0, contAttack_oculothorax = 0, contAttack_ogre = 0;
    int contJump_up = 0, contJump_down = 0;
    int contDeath = 0, death_flag = 0;
    int score = 0, score_trigger = 70, exit_game = 0;
    int hero_x = 50, hero_run = 10;

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_exit_clicked();
    void on_pushButton_options_clicked();
    void on_pushButton_open_clicked();
    void on_pushButton_comboBox_ports_currentIndexChanged(const QString &arg1);
    void on_pushButton_score_clicked();

    void open_Port();
    void run_Control();

    void run_Game();
    void run_Menu();
    void run_Score();
    void run_Hero_boss();

    void run_Animation();
    void run_Animation_special();
    void run_Animation_hero();
    void run_Animation_death();
    void run_Animation_jump();
    void run_Animation_enemy();
    void run_Animation_enemy_shockwave();

    void run_Enemy();
    void run_Enemy_kill();
    void run_Enemy_slime();
    void run_Enemy_oculothorax();
    void run_Enemy_ogre_boss();
    void run_Enemy_shockwave();
    void run_Enemy_slime_attack();
    void run_Enemy_oculothorax_attack();
    void run_Enemy_ogre_boss_attack();

    void run_Collision();
    void run_Collision_Enemy_slime();
    void run_Collision_Enemy_oculothorax();
    void run_Collision_Enemy_ogre_shockwave();

    void run_Background();
    void run_jump_Hero(); 

private:
    Ui::HeroJump *ui;

    QTimer *timer_run_game;
    QTimer *timer_animation_hero;
    QTimer *timer_animation_enemy;

    QSerialPort serial;
    QString nome;

    QMessageBox msg;
};

class EventFilter : public QObject
{
    Q_OBJECT
public:
     bool eventFilter(QObject *object, QEvent *event)override;
};

#endif // HEROJUMP_H
