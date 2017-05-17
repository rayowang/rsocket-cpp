// Copyright 2004-present Facebook. All Rights Reserved.

#include <gtest/gtest.h>
#include "src/framing/FrameTransport.h"
#include "src/temporary_home/NullRequestHandler.h"
#include "test/test_utils/InlineConnection.h"

using namespace ::testing;
using namespace ::rsocket;

TEST(FrameTransportTest, OnSubscribeAfterClose) {
  class NullSubscription : public rsocket::Subscription {
   public:
    // Subscription methods
    void request(size_t n) noexcept override {}
    void cancel() noexcept override {}
  };

  FrameTransport transport(std::make_unique<InlineConnection>());
  transport.close(std::runtime_error("test_close"));
  static_cast<Subscriber<std::unique_ptr<folly::IOBuf>>&>(transport)
      .onSubscribe(std::make_shared<NullSubscription>());
  // if we got here, we passed all the checks in the onSubscribe method
}
