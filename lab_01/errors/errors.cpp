#include "errors.h"

#include <QMessageBox>

void error_message(err_t error)
{
    QMessageBox messageBox;
    switch (error) {
    case SUCCESS:
        messageBox.critical(0, "Произошла ошибка!", "Ваш программист нехороший человек. Никаких ошибок нет ^_^.");
        break;
    case EMPTY_FILE_NAME:
        messageBox.critical(0, "Произошла ошибка!", "Имя файла не может быть пустым полем.");
        break;
    case OPEN_FILE_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Невозможно открыть файл.");
        break;
    case WRONG_FILE_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Неверный файл.");
        break;
    case WRONG_POINTS_PTR_ERR:
    case WRONG_NPOINTS_ERR:
    case WRONG_EDGES_PTR_ERR:
    case WRONG_NEDGES_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Неверная фигура. Загрузите корректную фигуру из файла.");
        break;
    case POINTS_ALLOC_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Недостаточно памяти, чтобы хранить точки.");
        break;
    case WRONG_FILE_PTR_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Ваш программист нехороший человек. Он где-то потерял ваш файл.");
        break;
    case EDGES_ALLOC_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Недостаточно памяти, чтобы хранить связи.");
        break;
    case FSAVE_NPOINTS_ERR:
    case FILE_DESC_OBTAIN_ERR:
    case FTRUNCATE_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Ошибка сохранения данных в файл.");
        break;
    case FSAVE_NEDGES_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Невозможно сохранить фигуру без связей.");
        break;
    case WRONG_POINT_INDEX_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Ошибка при работе с фигурой.");
        break;
    case WRONG_EDGE_ERR:
        messageBox.critical(0, "Произошла ошибка!", "Файл неверен.");
        break;
    case UNDEFINED_COMMAND:
        messageBox.critical(0, "Произошла ошибка!", "В программе произошел вызов неверной команды.");
        break;
    default:
        messageBox.critical(0, "Произошла ошибка!",
                            "Что-то пошло не так. Попробуйте позже."); /* Why is it even here? */
        break;
    }
}
