#include "mvPythonModule.h"
#include "Core/mvApp.h"
#include "Core/StandardWindows/mvAppLog.h"
#include "Core/AppItems/mvAppItems.h"
#include "mvPythonTranslator.h"
#include "mvInterfaces.h"
#include "mvInterfaceRegistry.h"

namespace Marvel {

	static std::map<std::string, mvPythonTranslator> Translators = mvInterfaceRegistry::GetRegistry()->getPythonInterface("sbPlot");

	std::map<std::string, mvPythonTranslator>& BuildPlottingInterface() {

		std::map<std::string, mvPythonTranslator>* translators = new std::map< std::string, mvPythonTranslator>{

			{"add_plot", mvPythonTranslator({
				{mvPythonDataType::String, "name"},
				{mvPythonDataType::Optional},
				{mvPythonDataType::String, "xAxisName"},
				{mvPythonDataType::String, "yAxisName"},
				{mvPythonDataType::KeywordOnly},
				{mvPythonDataType::Integer, "flags"},
				{mvPythonDataType::Integer, "xflags"},
				{mvPythonDataType::Integer, "yflags"}
			}, true, "Adds a plot widget.")},

			{"clear_plot", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
			}, false, "Clears a plot.")},

			{"set_color_map", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
				{mvPythonDataType::Integer, "map"}
			}, false, "Sets the color map of the plot's series.")},

			{"set_plot_xlimits", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
				{mvPythonDataType::Float, "xmin"},
				{mvPythonDataType::Float, "xmax"},
			}, false, "Sets x axis limits of a plot. (can be undone with set_plot_xlimits_auto()")},

			{"set_plot_ylimits", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
				{mvPythonDataType::Float, "ymin"},
				{mvPythonDataType::Float, "ymax"},
			}, false, "Sets y axis limits of a plot. (can be undone with set_plot_ylimits_auto()")},

			{"set_plot_xlimits_auto", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
			}, false, "Sets plots x limits to be automatic.")},

			{"set_plot_ylimits_auto", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
			}, false, "Sets plots y limits to be automatic.")},

			{"add_line_series", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
				{mvPythonDataType::String, "name"},
				{mvPythonDataType::FloatList, "data"},
				{mvPythonDataType::Optional},
				{mvPythonDataType::KeywordOnly},
				{mvPythonDataType::FloatList, "color"},
				{mvPythonDataType::Float, "weight"}
			}, false, "Adds a line series to a plot.")},

			{"add_scatter_series", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
				{mvPythonDataType::String, "name"},
				{mvPythonDataType::FloatList, "data"},
				{mvPythonDataType::Optional},
				{mvPythonDataType::KeywordOnly},
				{mvPythonDataType::Integer, "marker"},
				{mvPythonDataType::Float, "size"},
				{mvPythonDataType::Float, "weight"},
				{mvPythonDataType::FloatList, "outline"},
				{mvPythonDataType::FloatList, "fill"},
			}, false, "Adds a scatter series to a plot.")},

			{"add_text_point", mvPythonTranslator({
				{mvPythonDataType::String, "plot"},
				{mvPythonDataType::String, "name"},
				{mvPythonDataType::Float, "x"},
				{mvPythonDataType::Float, "y"},
				{mvPythonDataType::Optional},
				{mvPythonDataType::KeywordOnly},
				{mvPythonDataType::Bool, "vertical"},
				{mvPythonDataType::Integer, "xoffset"},
				{mvPythonDataType::Integer, "yoffset"}
			}, false, "Adds a point with text to a plot.")}

		};

		return *translators;
	}

	PyObject* clear_plot(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;

		if (!Translators["clear_plot"].parse(args, kwargs, __FUNCTION__, &plot))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		graph->clear();

		Py_RETURN_NONE;
	}

	PyObject* set_plot_xlimits_auto(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;

		if (!Translators["set_plot_xlimits_auto"].parse(args, kwargs, __FUNCTION__, &plot))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		graph->setXLimitsAuto();

		Py_RETURN_NONE;
	}

	PyObject* set_plot_ylimits_auto(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;

		if (!Translators["set_plot_ylimits_auto"].parse(args, kwargs, __FUNCTION__, &plot))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		graph->setYLimitsAuto();

		Py_RETURN_NONE;
	}

	PyObject* set_plot_xlimits(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;
		float xmin;
		float xmax;

		if (!Translators["set_plot_xlimits"].parse(args, kwargs, __FUNCTION__, &plot, &xmin, &xmax))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		graph->setXLimits(xmin, xmax);

		Py_RETURN_NONE;
	}

	PyObject* set_plot_ylimits(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;
		float ymin;
		float ymax;

		if (!Translators["set_plot_ylimits"].parse(args, kwargs, __FUNCTION__, &plot, &ymin, &ymax))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		graph->setYLimits(ymin, ymax);

		Py_RETURN_NONE;
	}

	PyObject* set_color_map(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;
		int map;

		if (!Translators["set_color_map"].parse(args, kwargs, __FUNCTION__, &plot, &map))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		graph->SetColorMap(map);

		Py_RETURN_NONE;
	}

	PyObject* add_plot(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		MV_STANDARD_CALLBACK_INIT();
		const char* name;
		const char* xAxisName = "";
		const char* yAxisName = "";
		int flags = 0;
		int xflags = 0;
		int yflags = 0;
		width = -1;
		height = -1;

		if (!Translators["add_plot"].parse(args, kwargs, __FUNCTION__, &name, &xAxisName, &yAxisName, &flags,
			&xflags, &yflags, MV_STANDARD_CALLBACK_PARSE))
			Py_RETURN_NONE;

		mvAppItem* item = new mvPlot("", name,xAxisName, yAxisName, width, height, flags, xflags, yflags);

		MV_STANDARD_CALLBACK_EVAL();

		Py_RETURN_NONE;
	}

	PyObject* add_line_series(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;
		const char* name;
		PyObject* data;
		float weight = 1.0f;
		PyObject* color = PyTuple_New(4);
		PyTuple_SetItem(color, 0, PyLong_FromLong(1000));
		PyTuple_SetItem(color, 1, PyLong_FromLong(0));
		PyTuple_SetItem(color, 2, PyLong_FromLong(0));
		PyTuple_SetItem(color, 3, PyLong_FromLong(255));

		if (!Translators["add_line_series"].parse(args, kwargs, __FUNCTION__, &plot, &name, &data, &color, &weight))
			Py_RETURN_NONE;

		if (!PyList_Check(data))
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " add line series requires a list of lists.");
			Py_RETURN_NONE;
		}

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);

		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}

		mvPlot* graph = static_cast<mvPlot*>(aplot);

		auto datapoints = mvPythonTranslator::getVectVec2(data);

		auto mcolor = mvPythonTranslator::getColor(color);
		if (mcolor.r > 999)
			mcolor.specified = false;

		mvSeries* series = new mvLineSeries(name, datapoints, weight, mcolor);

		graph->addSeries(series);

		Py_RETURN_NONE;
	}

	PyObject* add_scatter_series(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;
		const char* name;
		PyObject* data;
		int marker = 2;
		float size = 4.0f;
		float weight = 1.0f;
		PyObject* outline = PyTuple_New(4);
		PyTuple_SetItem(outline, 0, PyLong_FromLong(1000));
		PyTuple_SetItem(outline, 1, PyLong_FromLong(0));
		PyTuple_SetItem(outline, 2, PyLong_FromLong(0));
		PyTuple_SetItem(outline, 3, PyLong_FromLong(255));
		PyObject* fill = PyTuple_New(4);
		PyTuple_SetItem(fill, 0, PyLong_FromLong(1000));
		PyTuple_SetItem(fill, 1, PyLong_FromLong(0));
		PyTuple_SetItem(fill, 2, PyLong_FromLong(0));
		PyTuple_SetItem(fill, 3, PyLong_FromLong(255));

		if (!Translators["add_scatter_series"].parse(args, kwargs, __FUNCTION__, &plot, &name, &data, &marker,
			&size, &weight, &outline, &fill))
			Py_RETURN_NONE;

		if (!PyList_Check(data))
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " add scatter series requires a list of lists.");
			Py_RETURN_NONE;
		}

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);

		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}

		mvPlot* graph = static_cast<mvPlot*>(aplot);

		auto datapoints = mvPythonTranslator::getVectVec2(data);

		auto mmarkerOutlineColor = mvPythonTranslator::getColor(outline);
		if (mmarkerOutlineColor.r > 999)
			mmarkerOutlineColor.specified = false;

		auto mmarkerFillColor = mvPythonTranslator::getColor(fill);
		if (mmarkerFillColor.r > 999)
			mmarkerFillColor.specified = false;

		mvSeries* series = new mvScatterSeries(name, datapoints, marker, size, weight, mmarkerOutlineColor,
			mmarkerFillColor);

		graph->addSeries(series);

		Py_RETURN_NONE;
	}

	PyObject* add_text_point(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* plot;
		const char* name;
		float x;
		float y;
		int vertical = false;
		int xoffset = 0;
		int yoffset = 0;

		if (!Translators["add_text_point"].parse(args, kwargs, __FUNCTION__, 
			&plot, &name, &x, &y, &vertical, &xoffset, &yoffset))
			Py_RETURN_NONE;

		mvAppItem* aplot = mvApp::GetApp()->getItem(plot);
		if (aplot == nullptr)
		{
			std::string message = plot;
			mvAppLog::getLogger()->LogWarning(message + " plot does not exist.");
			Py_RETURN_NONE;
		}
		mvPlot* graph = static_cast<mvPlot*>(aplot);

		mvSeries* series = new mvLabelSeries(name, { {(float)x, (float)y}}, xoffset, yoffset, vertical);

		graph->addSeries(series);

		Py_RETURN_NONE;
	}

	mvPythonModule* CreatePlotInterface()
	{

		auto pyModule = new mvPythonModule("sbPlot", {});

		pyModule->addMethodD(clear_plot);
		pyModule->addMethodD(set_plot_xlimits_auto);
		pyModule->addMethodD(set_plot_ylimits_auto);
		pyModule->addMethodD(set_plot_xlimits);
		pyModule->addMethodD(set_plot_ylimits);
		pyModule->addMethodD(set_color_map);
		pyModule->addMethodD(add_plot);
		pyModule->addMethodD(add_line_series);
		pyModule->addMethodD(add_scatter_series);
		pyModule->addMethodD(add_text_point);

		return pyModule;
	}

}