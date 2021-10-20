#ifndef ACC_ENV_DEFAULT_SERVICE_H
#define ACC_ENV_DEFAULT_SERVICE_H

#include "accenv/IAccEnv.h"
#include "accenv/AccEnvDefault_axl.h"

using namespace Arcane;

class AccEnvDefaultService : public ArcaneAccEnvDefaultObject
{
 public:
  AccEnvDefaultService(const ServiceBuildInfo & sbi);

  virtual ~AccEnvDefaultService() {}

 public:
  void initAcc() override;

  ax::Runner& runner() override { return m_runner; }
  ax::RunQueue newQueue() override { return makeQueue(m_runner); }

  UnstructuredMeshConnectivityView& connectivityView() override { return m_connectivity_view; }
  const UnstructuredMeshConnectivityView& connectivityView() const override { return m_connectivity_view; }
  
  void initMesh(ICartesianMesh* cartesian_mesh) override;

  Span<const Int16> nodeIndexInCells() const { return m_node_index_in_cells.constSpan(); }
  Span<const Int16> nodeIndexInFaces() const { return m_node_index_in_faces.constSpan(); }

  Integer maxNodeCell() const override { return 8; }
  Integer maxNodeFace() const override { return 4; }

 protected:

  void _computeNodeIndexInCells();
  void _computeNodeIndexInFaces();

 protected:
  ax::Runner m_runner;
  UnstructuredMeshConnectivityView m_connectivity_view;

  UniqueArray<Int16> m_node_index_in_cells;
  UniqueArray<Int16> m_node_index_in_faces;
};

#endif

