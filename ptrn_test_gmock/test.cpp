#include "pch.h"



extern "C" {
#include <stdio.h>   // for sprintf

#include "states_semaforo_default.h" // определяем тут StateSemaforoPtr, StateSemEvents
#include "states_semaforo_implement.h"
#include "states_semaforo_internal.h"
// состояние
#include "state_yellow.h"
    // завершение объявления
    struct SemaforoMaker {
        long tickTimeWork;
        struct StateSemaforo state;
    };

    extern SemaforoMakerPtr _instance;
}
namespace BaseTestGmockNamespace {

    TEST(TestCaseName, TestNameDymmy) {
        EXPECT_EQ(1, 1);
        EXPECT_TRUE(true);
    }

    TEST(SemaforoTest, Test_04_StateFunctionsNotNull) {
        SemaforoMakerPtr semaforo = createSemaforo();

        EXPECT_NE(semaforo->state.state_yellow, nullptr);
        EXPECT_NE(semaforo->state.state_red, nullptr);
        EXPECT_NE(semaforo->state.state_red_yellow, nullptr);
        EXPECT_NE(semaforo->state.state_green, nullptr);
        EXPECT_NE(semaforo->state.state_green_blink, nullptr);
        EXPECT_NE(semaforo->state.state_yellow_blink, nullptr);

        destroySemaforo(semaforo);
    }
}
namespace TestLearn {

    int fxn1(void) {
        std::cout << "Hello" << std::endl;
        return 10;
    }
    int fxn2(void) {
        return 20;
    }
    void work_fxn(void) {
        int value = 0;
        value = fxn1();

        if (value > 10) {

        }

        value = fxn2();
        if (value > 20) {

        }
    }
    class MockTest {
    public:
        MOCK_METHOD(int, fxn1, (), ());
        MOCK_METHOD(int, fxn2, (), ());
    };
    static MockTest* g_mock = nullptr;

    static void c_fxn1() { g_mock->fxn1(); }
    static void c_fxn2() { g_mock->fxn2(); }

}

namespace TestTransition{

    class MockTest {
    public:
        MOCK_METHOD(void, on_entry, (), ());
        MOCK_METHOD(void, on_do, (), ());
        MOCK_METHOD(void, on_exit, (), ());
        MOCK_METHOD(long, check_change_state, (), ());
    };
    static MockTest* g_mock = nullptr;

    static void c_on_entry() { g_mock->on_entry(); }
    static void c_on_do() { g_mock->on_do(); }
    static void c_on_exit() { g_mock->on_exit(); }
    static long c_check_change_state() { return g_mock->check_change_state(); }

    // чтобы не писать testing::
    //using testing::InSequence;
    //using testing::Return;
/*
Тест. Простой тест переключения в состояние
1. Срабатывания on_entry() при входе.
2. Возврат времени check_change_state() == 16 при первом вхождении.
3. Выполнение on_do()
4. Возврат времени check_change_state() == 20 при втором выполнении. 
5. Выполнение on_exit() при выходе.
*/
    TEST(YellowStateTest, SwitchToRedWhenTimeout)
    {
        MockTest mock;
        g_mock = &mock;

        //EXPECT_CALL(mock, check_change_state())
        //    .WillOnce(::testing::Return(10))
        //    .WillOnce(::testing::Return(20));
        // Описываем порядок вызова. Именно тот ожидаемый порядок
        // который будет при выполнении.
        {
            testing::InSequence seq; // чтобы видеть порядок
            EXPECT_CALL(mock, on_entry());

            // первый раз возвращает 0, почему-то
            EXPECT_CALL(mock, check_change_state())     // #1
                .WillOnce(testing::Return(16));

            EXPECT_CALL(mock, on_do());

            EXPECT_CALL(mock, check_change_state())     // #1
                .WillOnce(testing::Return(20));

            EXPECT_CALL(mock, on_exit());
            //EXPECT_CALL(mock, on_exit()); // покажет что не вызывается.
            //EXPECT_CALL(mock, on_do()).Times(1);
        }
        StateSemaforo s{};
        transitionToYellow(&s);

        StateSemEvents events{
            .on_entry = c_on_entry,
            .on_do = c_on_do,
            .on_exit = c_on_exit,
            .check_change_state = c_check_change_state,
            .workTimeToSwitch = 3 
        };

        s.state_yellow(&s, events);

        ASSERT_STREQ(s.name, "red_state");
    }
/*
Тест запуска on_do каждый раз при выполнении состояния
1. При первом вхождении выполняется on_enrty один раз.
2. При первом вхождении check_change_state возвращает 0.

Далее идут последующие вхождения:
3. Выполняется on_do TIMES_TO_RUN.
4. На последующих вхождения check_change_state возвращает 1.
5. На последнем вхождении check_change_state возвращает 3.
6. Выполняется on_exit().

*/
    TEST(YellowStateTest, testOnDo)
    {
        MockTest mock;
        g_mock = &mock;
        const auto TIMES_TO_RUN = 1000;

        //// решение в лоб, но съедает стек. При TIMES_TO_RUN = 1000 переполнение стека
        //// START BRUTFORCE
        //{
        //    testing::InSequence seq; // Включаем строгий режим

        //    // 1. Вход
        //    EXPECT_CALL(mock, on_entry()).Times(1);

        //    // 2. Первый проход (специфичный, check возвращает 0)
        //    EXPECT_CALL(mock, check_change_state())
        //        .WillOnce(testing::Return(0));

        //    EXPECT_CALL(mock, on_do()).Times(1);

        //    EXPECT_CALL(mock, check_change_state())
        //        .WillOnce(testing::Return(1)); // Возвращаем 1 ровно 1 раз

        //    // 3. Цикл чередования (со 2-го по предпоследний раз)
        //    // Мы генерируем "бусы" ожиданий: Do -> Check -> Do -> Check ...
        //    for (int i = 0; i < TIMES_TO_RUN - 2; ++i) {
        //        EXPECT_CALL(mock, on_do())
        //            .Times(1); // Ждем ровно 1 раз

        //        EXPECT_CALL(mock, check_change_state())
        //            .WillOnce(testing::Return(1)); // Возвращаем 1 ровно 1 раз
        //    }

        //    // 4. Последний проход (check возвращает 3/5)
        //    EXPECT_CALL(mock, on_do()).Times(1);
        //    EXPECT_CALL(mock, check_change_state())
        //        .WillOnce(testing::Return(5)); // Код выхода

        //    // 5. Выход
        //    EXPECT_CALL(mock, on_exit()).Times(1);
        //}
        //// END BRUTFORCE
    // Флаг для проверки чередования.
    // false = ждем on_do
    // true  = ждем check_change_state
        bool waiting_for_check = true;

        // Переменная для подсчета вызовов check
        int check_calls = 0;
        int check_1 = 0;
        int check_2 = 0;

        {
            testing::InSequence seq;
            EXPECT_CALL(mock, on_entry()).Times(1);

            // Дальше мы не используем InSequence для тела цикла,
            // так как порядок мы контролируем флагом waiting_for_check
        }

        // == Настройка поведения on_do ==
        // Он вызывается между проверками.
        // Всего вызовов на 1 меньше, чем проверок (так как последняя проверка уводит на выход)
        EXPECT_CALL(mock, on_do())
        .Times(TIMES_TO_RUN-1)
        .WillRepeatedly(testing::Invoke([&]() -> void {
            // Если пришли в on_do, а ждали check (значит два on_do подряд или забыли check)
            if (waiting_for_check) {
                ADD_FAILURE() << "Order violation: on_do called when check was expected!";
                return;
            }
            // Теперь мы выполнили работу, следующей должна быть проверка
            waiting_for_check = true;
            check_1++;
            }));

        // == Настройка поведения check_change_state ==
        EXPECT_CALL(mock, check_change_state())
        .Times(TIMES_TO_RUN) 
        .WillRepeatedly(testing::Invoke([&]() -> int {
            // Если пришли в check, а ждали on_do (значит два check подряд)
            if (!waiting_for_check) {
                ADD_FAILURE() << "Order violation: check called when on_do was expected! " << check_calls;
                return 0;
            }

            // Проверка выполнена, теперь разрешаем on_do
            waiting_for_check = false;

            check_calls++;

            // Сценарий возвращаемых значений:
            if (check_calls == 1) return 0;             // Первый вход
            if (check_calls == TIMES_TO_RUN) return 5;  // Последний вход -> выход
            return 1;                                   // Обычная работа
            }));

        // == Выход ==
        EXPECT_CALL(mock, on_exit()).Times(1);


        StateSemaforo s{};
        transitionToYellow(&s);

        StateSemEvents events{
            .on_entry = c_on_entry,
            .on_do = c_on_do,
            .on_exit = c_on_exit,
            .check_change_state = c_check_change_state,
            .workTimeToSwitch = 3
        };

        for (int i = 0; i < TIMES_TO_RUN; i++) {
            s.state_yellow(&s, events);
        }

        ASSERT_STREQ(s.name, "red_state");
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}