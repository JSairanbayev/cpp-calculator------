#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->cmb_controller, &QComboBox::currentIndexChanged,
            this, &MainWindow::HandleControllerChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> callback) {
    digit_callback_ = callback;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> callback) {
    operation_callback_ = callback;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> callback) {
    control_callback_ = callback;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> callback) {
    controller_callback_ = callback;
}

void MainWindow::on_tb_zero_clicked() {
    if (digit_callback_) {
        digit_callback_(0);
    }
}

void MainWindow::on_tb_one_clicked() {
    if (digit_callback_) {
        digit_callback_(1);
    }
}

void MainWindow::on_tb_two_clicked() {
    if (digit_callback_) {
        digit_callback_(2);
    }
}

void MainWindow::on_tb_three_clicked() {
    if (digit_callback_) {
        digit_callback_(3);
    }
}

void MainWindow::on_tb_four_clicked() {
    if (digit_callback_) {
        digit_callback_(4);
    }
}

void MainWindow::on_tb_five_clicked() {
    if (digit_callback_) {
        digit_callback_(5);
    }
}

void MainWindow::on_tb_six_clicked() {
    if (digit_callback_) {
        digit_callback_(6);
    }
}

void MainWindow::on_tb_seven_clicked() {
    if (digit_callback_) {
        digit_callback_(7);
    }
}

void MainWindow::on_tb_eight_clicked() {
    if (digit_callback_) {
        digit_callback_(8);
    }
}

void MainWindow::on_tb_nine_clicked() {
    if (digit_callback_) {
        digit_callback_(9);
    }
}

void MainWindow::on_tb_add_clicked() {
    if (operation_callback_) {
        operation_callback_(Operation::ADDITION);
    }
}

void MainWindow::on_tb_substract_clicked() {
    if (operation_callback_) {
        operation_callback_(Operation::SUBTRACTION);
    }
}

void MainWindow::on_tb_multiplicate_clicked() {
    if (operation_callback_) {
        operation_callback_(Operation::MULTIPLICATION);
    }
}

void MainWindow::on_tb_divide_clicked() {
    if (operation_callback_) {
        operation_callback_(Operation::DIVISION);
    }
}

void MainWindow::on_tb_power_clicked() {
    if (operation_callback_) {
        operation_callback_(Operation::POWER);
    }
}

void MainWindow::on_tb_equal_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::EQUALS);
    }
}

void MainWindow::on_tb_reset_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::CLEAR);
    }
}

void MainWindow::on_tb_negate_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::PLUS_MINUS);
    }
}

void MainWindow::on_tb_backspace_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::BACKSPACE);
    }
}

void MainWindow::on_tb_ms_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::MEM_SAVE);
    }
}

void MainWindow::on_tn_mr_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::MEM_LOAD);
    }
}

void MainWindow::on_tb_mc_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::MEM_CLEAR);
    }
}

void MainWindow::on_tb_extra_clicked() {
    if (control_callback_) {
        control_callback_(ControlKey::EXTRA_KEY);
    }
}

void MainWindow::HandleControllerChanged(int index) {
    if (!controller_callback_) {
        return;
    }
    switch (index) {
    case 0:
        controller_callback_(ControllerType::DOUBLE);
        break;
    case 1:
        controller_callback_(ControllerType::FLOAT);
        break;
    case 2:
        controller_callback_(ControllerType::UINT8_T);
        break;
    case 3:
        controller_callback_(ControllerType::INT);
        break;
    case 4:
        controller_callback_(ControllerType::INT64_T);
        break;
    case 5:
        controller_callback_(ControllerType::SIZE_T);
        break;
    case 6:
        controller_callback_(ControllerType::RATIONAL);
        break;
    }
}