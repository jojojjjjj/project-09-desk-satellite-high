# 作业 | Assignments

本目录包含桌面卫星气象站项目的**作业提交模板与评分表**。原始参考工作表见下方私有子模块。

> This directory holds the **assignment submission templates and rubrics** for the Desk Satellite project. The original reference worksheets are in the private submodule below.

## 文件清单 | Files

| 文件 File | 说明 Description |
|-----------|------------------|
| `week-1-checkin.md` | 第一周进度报告模板 \| Week-1 check-in report template |
| `week-2-checkin.md` | 第二周进度报告模板 \| Week-2 check-in report template |
| `final-presentation.md` | 最终展示要求 \| Final presentation requirements |
| `rubric.md` | 详细评分表 \| Detailed grading rubric |

作业设计的完整说明见 `curriculum/assignments.md`。
> Full assignment-design notes are in `curriculum/assignments.md`.

---

## 🔒 原始工作表（私有子模块）| Source Worksheets (Private Submodule)

本项目作业改编所参考的 UPenn ESE5190 原始工作表存放在 `WorkSheet/` 子模块中，该子模块指向一个**私有仓库**，仅授权用户可访问。

> The original UPenn ESE5190 worksheets referenced by these assignments live in the `WorkSheet/` submodule, which points to a **private repository** — authorized access only.

- **仓库地址 | Repository URL**：`https://github.com/jojojjjjj/project-09-worksheet.git`（🔒 私有 \| private）

### 拉取方式 | How to Pull

**方式 A | Method A — 直接克隆（推荐）| Clone directly (recommended)**

```bash
git clone https://github.com/jojojjjjj/project-09-worksheet.git
```

未授权会报 `could not read Username` 或 `403 Forbidden`。
> Without permission you'll get `could not read Username` or `403 Forbidden`.

**方式 B | Method B — 通过父仓库子模块 | Via the parent repo's submodule**

```bash
# 在本仓库根目录执行 | run from the repo root
git submodule update --init assignments/WorkSheet
```

> ⚠️ 该子模块为私有，未授权用户执行此命令会失败（**预期行为**，用于访问控制）。授权用户请先配置 GitHub 凭据（`gh auth login` / SSH key / credential helper）。
> The submodule is private, so this command fails for unauthorized users (**intentional** access control). Authorized users must configure GitHub credentials first (`gh auth login` / SSH key / credential helper).

更多说明见项目根目录 `README.md` 的「作业工作表（私有子模块）」一节。
> More details in the "Worksheet (Private Submodule)" section of the root `README.md`.
