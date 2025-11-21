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
Тест
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
        const auto TIMES_TO_RUN = 10;

        {
            testing::InSequence seq; // Включаем строгий режим

            // 1. Вход
            EXPECT_CALL(mock, on_entry()).Times(1);

            // 2. Первый проход (специфичный, check возвращает 0)
            EXPECT_CALL(mock, check_change_state())
                .WillOnce(testing::Return(0));

            EXPECT_CALL(mock, on_do()).Times(1);

            EXPECT_CALL(mock, check_change_state())
                .WillOnce(testing::Return(1)); // Возвращаем 1 ровно 1 раз

            // 3. Цикл чередования (со 2-го по предпоследний раз)
            // Мы генерируем "бусы" ожиданий: Do -> Check -> Do -> Check ...
            for (int i = 0; i < TIMES_TO_RUN - 2; ++i) {
                EXPECT_CALL(mock, on_do())
                    .Times(1); // Ждем ровно 1 раз

                EXPECT_CALL(mock, check_change_state())
                    .WillOnce(testing::Return(1)); // Возвращаем 1 ровно 1 раз
            }

            // 4. Последний проход (check возвращает 3/5)
            EXPECT_CALL(mock, on_do()).Times(1);
            EXPECT_CALL(mock, check_change_state())
                .WillOnce(testing::Return(5)); // Код выхода

            // 5. Выход
            EXPECT_CALL(mock, on_exit()).Times(1);
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