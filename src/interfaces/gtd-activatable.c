/* gtd-activatable.c
 *
 * Copyright (C) 2015 Georges Basile Stavracas Neto <georges.stavracas@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtd-activatable.h"
#include "gtd-panel.h"
#include "gtd-provider.h"

G_DEFINE_INTERFACE (GtdActivatable, gtd_activatable, PEAS_TYPE_ACTIVATABLE)

enum
{
  PANEL_ADDED,
  PANEL_REMOVED,
  PROVIDER_ADDED,
  PROVIDER_CHANGED,
  PROVIDER_REMOVED,
  NUM_SIGNALS
};

static guint signals[NUM_SIGNALS] = { 0, };

static void
gtd_activatable_default_init (GtdActivatableInterface *iface)
{
  /**
   * GtdActivatable::panels:
   *
   * A list of #GtdPanel this plugin carries.
   */
  g_object_interface_install_property (iface,
                                       g_param_spec_pointer ("panels",
                                                             "Panels this widget has",
                                                             "A list of panel this widget has",
                                                             G_PARAM_READABLE));

  /**
   * GtdActivatable::providers:
   *
   * A list of #GtdProvider this plugin carries.
   */
  g_object_interface_install_property (iface,
                                       g_param_spec_pointer ("providers",
                                                             "Providers this widget has",
                                                             "A list of providers this widget has",
                                                             G_PARAM_READABLE));

  /**
   * GtdActivatable::panel-added:
   *
   * The ::panel-added signal is emmited after a #GtdPanel
   * is connected.
   */
  signals[PANEL_ADDED] = g_signal_new ("panel-added",
                                       GTD_TYPE_ACTIVATABLE,
                                       G_SIGNAL_RUN_LAST,
                                       0,
                                       NULL,
                                       NULL,
                                       NULL,
                                       G_TYPE_NONE,
                                       1,
                                       GTD_TYPE_PANEL);

  /**
   * GtdActivatable::panel-removed:
   *
   * The ::panel-removed signal is emmited after a #GtdPanel
   * is removed from the list.
   */
  signals[PANEL_REMOVED] = g_signal_new ("panel-removed",
                                         GTD_TYPE_ACTIVATABLE,
                                         G_SIGNAL_RUN_LAST,
                                         0,
                                         NULL,
                                         NULL,
                                         NULL,
                                         G_TYPE_NONE,
                                         1,
                                         GTD_TYPE_PANEL);

  /**
   * GtdActivatable::provider-added:
   *
   * The ::provider-added signal is emmited after a #GtdProvider
   * is connected.
   */
  signals[PROVIDER_ADDED] = g_signal_new ("provider-added",
                                          GTD_TYPE_ACTIVATABLE,
                                          G_SIGNAL_RUN_LAST,
                                          0,
                                          NULL,
                                          NULL,
                                          NULL,
                                          G_TYPE_NONE,
                                          1,
                                          GTD_TYPE_PROVIDER);

  /**
   * GtdActivatable::provider-changed:
   *
   * The ::provider-changed signal is emmited after a #GtdProvider
   * has any of it's properties changed.
   */
  signals[PROVIDER_CHANGED] = g_signal_new ("provider-changed",
                                            GTD_TYPE_ACTIVATABLE,
                                            G_SIGNAL_RUN_LAST,
                                            0,
                                            NULL,
                                            NULL,
                                            NULL,
                                            G_TYPE_NONE,
                                            1,
                                            GTD_TYPE_PROVIDER);

  /**
   * GtdActivatable::provider-removed:
   *
   * The ::provider-removed signal is emmited after a #GtdProvider
   * is disconnected.
   */
  signals[PROVIDER_REMOVED] = g_signal_new ("provider-removed",
                                            GTD_TYPE_ACTIVATABLE,
                                            G_SIGNAL_RUN_LAST,
                                            0,
                                            NULL,
                                            NULL,
                                            NULL,
                                            G_TYPE_NONE,
                                            1,
                                            GTD_TYPE_PROVIDER);
}

GList*
gtd_activatable_get_panels (GtdActivatable *activatable)
{
  g_return_val_if_fail (GTD_IS_ACTIVATABLE (activatable), NULL);
  g_return_val_if_fail (GTD_ACTIVATABLE_GET_IFACE (activatable)->get_panels, NULL);

  return GTD_ACTIVATABLE_GET_IFACE (activatable)->get_panels (activatable);
}

GList*
gtd_activatable_get_providers (GtdActivatable *activatable)
{
  g_return_val_if_fail (GTD_IS_ACTIVATABLE (activatable), NULL);
  g_return_val_if_fail (GTD_ACTIVATABLE_GET_IFACE (activatable)->get_providers, NULL);

  return GTD_ACTIVATABLE_GET_IFACE (activatable)->get_providers (activatable);
}
