/*******************************************************************************
 * Copyright 上海赜睿信息科技有限公司(Zilliz) - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Proprietary and confidential.
 ******************************************************************************/
#pragma once

#include "VecServiceScheduler.h"
#include "utils/Error.h"
#include "db/Types.h"

#include "thrift/gen-cpp/VectorService_types.h"

#include <condition_variable>
#include <memory>

namespace zilliz {
namespace vecwise {
namespace server {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AddGroupTask : public BaseTask {
public:
    static BaseTaskPtr Create(int32_t dimension,
                              const std::string& group_id);

protected:
    AddGroupTask(int32_t dimension,
                 const std::string& group_id);

    ServerError OnExecute() override;

private:
    int32_t  dimension_;
    std::string group_id_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GetGroupTask : public BaseTask {
public:
    static BaseTaskPtr Create(const std::string& group_id, int32_t&  dimension);

protected:
    GetGroupTask(const std::string& group_id, int32_t&  dimension);

    ServerError OnExecute() override;


private:
    std::string group_id_;
    int32_t&  dimension_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DeleteGroupTask : public BaseTask {
public:
    static BaseTaskPtr Create(const std::string& group_id);

protected:
    DeleteGroupTask(const std::string& group_id);

    ServerError OnExecute() override;


private:
    std::string group_id_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AddVectorTask : public BaseTask {
public:
    static BaseTaskPtr Create(const std::string& group_id,
                              const VecTensorList &tensor_list);

protected:
    AddVectorTask(const std::string& group_id,
                  const VecTensorList &tensor_list);

    ServerError OnExecute() override;


private:
    std::string group_id_;
    const VecTensorList& tensor_list_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SearchVectorTask : public BaseTask {
public:
    static BaseTaskPtr Create(VecSearchResultList& result,
                              const std::string& group_id,
                              const int64_t top_k,
                              const VecTensorList& tensor_list,
                              const VecTimeRangeList& time_range_list);

protected:
    SearchVectorTask(VecSearchResultList& result,
                     const std::string& group_id,
                     const int64_t top_k,
                     const VecTensorList& tensor_list,
                     const VecTimeRangeList& time_range_list);

    ServerError OnExecute() override;


private:
    VecSearchResultList& result_;
    std::string group_id_;
    int64_t top_k_;
    const VecTensorList& tensor_list_;
    const VecTimeRangeList& time_range_list_;
};

}
}
}