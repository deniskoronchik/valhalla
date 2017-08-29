#include "meili/topk_search.h"

namespace valhalla {
namespace meili {

float EnlargedEmissionCostModel::operator()(const StateId& stateid) const
{
  const auto& model = evs_.original_emission_cost_model();
  const auto& original_stateid = evs_.GetOrigin(stateid);
  if (original_stateid.IsValid()) {
    return model(original_stateid);
  }
  if (stateid.time() == 0 && evs_.GetClone(stateid).IsValid()) {
    return -1.0;
  } else {
    return model(stateid);
  }
}

float EnlargedTransitionCostModel::operator()(const StateId& lhs, const StateId& rhs) const
{
  const auto& model = evs_.original_transition_cost_model();
  const auto& original_lhs = evs_.GetOrigin(lhs);
  const auto& original_rhs = evs_.GetOrigin(rhs);
  if (original_lhs.IsValid()) {
    if (original_rhs.IsValid()) {
      return model(original_lhs, original_rhs);
    } else {
      if (evs_.GetClone(rhs).IsValid()) {
        return -1.0;
      } else {
        return model(original_rhs, rhs);
      }
    }
  } else {
    if (original_rhs.IsValid()) {
      return -1.0;
    } else {
      return model(lhs, rhs);
    }
  }
}

void EnlargedViterbiSearch::ClonePath(const StateId::Time& time)
{
  for (auto it = vs_.SearchPath(time); it != vs_.PathEnd(); it++) {
    const auto& origin = *it;
    if (origin.IsValid()) {
      // TODO: clone(it->time(), UUID())
      StateId clone;
      origin_[clone] = origin;
      clone_[origin] = clone;
    }
  }

  // Add the clones to vs_
  for (const auto& pair: origin_) {
    vs_.AddStateId(pair.first);
  }
}

void TopKSearch::RemovePath(const StateId::Time& time)
{
  evss_.emplace_back(vs_);
  evss_.back().ClonePath(time);
}

}
}
