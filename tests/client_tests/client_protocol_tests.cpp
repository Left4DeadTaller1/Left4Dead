#include <gtest/gtest.h>

#include "action_client.h"
#include "action_create.h"
#include "action_join.h"
#include "action_start_move.h"
#include "action_end_shoot.h"

TEST(CreateSerializeTest, SerializeTest) {
  CreateAction createAction("Pepe", RIFLE, WAR2_BRIGHT);

  // Tipo de accion (1 byte) = CREATE
  // Tipo de arma (1 byte) = RIFLE
  // Tipo de mapa (1 byte) = WAR2_BRIGHT
  // Largo del nickname (1 byte) = 4
  // nickname (4 byte) = Pepe

  std::vector<int8_t> actionSerialize = createAction.serialize();

  EXPECT_EQ(8, actionSerialize.size());
  EXPECT_EQ(CREATE, actionSerialize[0]);
  EXPECT_EQ(static_cast<int8_t>(RIFLE), actionSerialize[1]);
  EXPECT_EQ(static_cast<int8_t>(WAR2_BRIGHT), actionSerialize[2]);
  EXPECT_EQ(4, actionSerialize[3]);
  EXPECT_EQ('P', actionSerialize[4]);
  EXPECT_EQ('e', actionSerialize[5]);
  EXPECT_EQ('p', actionSerialize[6]);
  EXPECT_EQ('e', actionSerialize[7]);
}

TEST(JoinSerializeTest, SerializeTest) {
  JoinAction joinAction("Pepe", SNIPER, 1);

  // Tipo de accion (1 byte) = JOIN
  // Tipo de arma (1 byte) = SNIPER
  // codigo de partida (1 byte) = 1
  // Largo del nickname (1 byte) = 4
  // nickname (4 byte) = Pepe

  std::vector<int8_t> actionSerialize = joinAction.serialize();

  EXPECT_EQ(8, actionSerialize.size());

  EXPECT_EQ(JOIN, actionSerialize[0]);
  EXPECT_EQ(1, actionSerialize[1]);
  EXPECT_EQ(static_cast<int8_t>(SNIPER), actionSerialize[2]);
  EXPECT_EQ(4, actionSerialize[3]);
  EXPECT_EQ('P', actionSerialize[4]);
  EXPECT_EQ('e', actionSerialize[5]);
  EXPECT_EQ('p', actionSerialize[6]);
  EXPECT_EQ('e', actionSerialize[7]);
}

TEST(StartMoveWalkSerializeTest, SerializeTest) {
  StartMove startMove(RUN, RIGHT);

  std::vector<int8_t> serializedData = startMove.serialize();

  EXPECT_EQ(4, serializedData.size());

  EXPECT_EQ(START_MOVE, serializedData[0]);
  EXPECT_EQ(static_cast<int8_t>(RUN), serializedData[1]);
  EXPECT_EQ(1, serializedData[2]);
  EXPECT_EQ(3, serializedData[3]);
}

TEST(StartMoveRunSerializeTest, SerializeTest) {
  StartMove startMove(WALK, DOWN);

  std::vector<int8_t> serializedData = startMove.serialize();

  EXPECT_EQ(4, serializedData.size());

  EXPECT_EQ(START_MOVE, serializedData[0]);
  EXPECT_EQ(static_cast<int8_t>(WALK), serializedData[1]);
  EXPECT_EQ(3, serializedData[2]);
  EXPECT_EQ(1, serializedData[3]);
}


