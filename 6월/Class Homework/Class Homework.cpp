// Class Homework.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdlib>
#include "pch.h"

using namespace std;

//최상위 클래스 Creature ... 추상클래스
//--Player
// --Knight
// --Archer
// --Mage

//--Monster

// 사양서1
// 1. 1~3의 수를 입력받아서 Knight, Archer, Mage 세 직업 중 하나를 선택해 생성(동적할당)하게 해주세요.
// 2. 컴퓨터도 난수를 받아서 1.과 같이 세팅해주세요.
// 3. 플레이어의 이름을 입력받고 Set해주세요. 컴퓨터는 컴퓨터로
// 4. 공격할 때 서로의 이름이 표시되게해주세요. 예) Hanil이 컴퓨터를 공격했습니다.
// 5. Knight는 체력이 50프로 미만이 되면 공격력이 2배 강해집니다.
// 6. Mage는 마나를 5만큼 소비하여 공격을 합니다. 공격할 때 마나가 부족하다면 50만큼 회복하고 공격을 쉽니다.
// 7. Archer 30프로 확률로 크리티컬 데미지(3배 공격)을 합니다.
// 8. 이 때 누가 이기는지 체크하고 이길 때 까지 반복

// 사양서2
// 0. 컴퓨터와 전투할지 사냥으로 경험치를 얻을지 1,2 입력으로 선택(컴퓨터와 전투 패배시 혹은 고블린과 전투 후)
// 1. Creature 상속받는 Player 만듭니다.
// 2. 사양서1의 Knight와 Archer, Mage는 Player를 상속받습니다. 이 때 Player는 추상클래스입니다.
// 3. Player의 속성에서 경험치가 추가됩니다.
// 4. Player가 고블린 10마리와 싸우는 전투에서 경험치를 얻고 경험치에 따라서 스탯이 올라갑니다.
// 5. 전투가 끝나고 사양서1의 게임을 다시해서 이기면 프로그램 종료

int main()
{
    srand(time(nullptr));

    World* world = new World();

    while (true) {
        world->Battle1();
        
        if (world->End())
            break;
    }

    delete world;
    
    return 0;
}
