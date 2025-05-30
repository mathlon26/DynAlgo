#ifndef CANDLECLOSEEVENTOBSERVER_H
#define CANDLECLOSEEVENTOBSERVER_H

#include <QObject>
#include <QDateTime>
#include <QMap>
#include <functional>

#include "trading/event/EventHandler.h"
#include "trading/event/type/CandleClose.h"
/*
 * CandleCloseEventObserver
 *
 * - Registers one factory per interval (in minutes). For “month” we use 43200,
 *   and for “year” we use 525600, as described below.
 *
 * - On construction, each interval’s “lastDispatched” is set to the most recent close
 *   (so that we do not immediately fire a ton of historical events).
 *
 * - poll() should be called frequently (e.g. every 100 ms). Each time it runs,
 *   it computes what “now”’s latest candle‐close should be. If that timestamp is
 *   strictly greater than what we last dispatched for that interval, we create a new
 *   CandleClose* via the factory, set its closeTime, hand it off to EventHandler,
 *   and update lastDispatched.
 *
 *   – Fixed‐minute intervals (1, 5, 15, 30, 60, 120, 240, 480, 720, 1440, 10080, etc.)
 *     are handled by integer division of the UTC epoch. E.g. for an N‐minute candle:
 *       QDateTime::currentDateTimeUtc().toSecsSinceEpoch() / (N*60)
 *     yields the “number of full N‐minute buckets since epoch,” then we multiply
 *     back by N*60 to recover the exact close time in epoch‐seconds.
 *
 *   – For “month” (intervalMinutes = 43200), we compute the very latest “first‐of‐month 00:00 UTC”
 *     that is ≤ now. That first‐of‐this‐month 00:00 UTC is when the last month closed.
 *
 *   – For “year” (intervalMinutes = 525600), we compute the very latest “January 1 00:00 UTC”
 *     that is ≤ now. That Jan 1 00:00 UTC is when the last year closed.
 *
 * Usage example (in your application startup):
 *
 *   auto handler = new EventHandler(...);
 *   auto observer = new CandleCloseEventObserver(handler, parentQObject);
 *   // Internally, constructor has called registerCandleEvent(...) for all known intervals.
 *   // Then your main loop should call observer->poll() every 100 ms or so.
 *
 */

class CandleCloseEventObserver : public QObject
{
    Q_OBJECT

public:
    explicit CandleCloseEventObserver(EventHandler* handler, QObject* parent = nullptr);

    /// Called periodically (e.g. every 100 ms) by whatever scheduler you have.
    void poll();

private:
    /// Register a factory that produces a new CandleClose subclass (e.g. m1CandleCloseEvent)
    /// whenever a candle of `intervalMinutes` must be fired.
    ///
    /// intervalMinutes:
    ///   - For truly fixed‐minute intervals, use 1, 5, 15, 30, 60, 120, 240, 480, 720, 1440, 10080, etc.
    ///   - For “month,” pass 43200 (i.e. 30 days × 24 h × 60 min = 43200).
    ///     (Actually “month” means “monthly boundary,” which we compute as first-of-month 00:00 UTC.)
    ///   - For “year,” pass 525600 (i.e. 365 days × 24 h × 60 min = 525600).
    ///     (Actually “year” means “yearly boundary,” which we compute as Jan 1 00:00 UTC.)
    void registerCandleEvent(int intervalMinutes, std::function<CandleClose*()> factory);

    /// Given “now” and a fixed‐minute interval (e.g. 5), return the QDateTime (UTC)
    /// of the last time that an N‐minute candle exactly closed.
    QDateTime calculateLastFixedCandleClose(const QDateTime& nowUtc, int intervalMinutes) const;

    /// Given “now,” return the QDateTime (UTC) of the most recent “first of month 00:00 UTC”
    /// that is ≤ nowUtc. That instant is when the previous monthly candle closed.
    QDateTime calculateLastMonthlyClose(const QDateTime& nowUtc) const;

    /// Given “now,” return the QDateTime (UTC) of the most recent “January 1 00:00 UTC”
    /// that is ≤ nowUtc. That instant is when the previous yearly candle closed.
    QDateTime calculateLastYearlyClose(const QDateTime& nowUtc) const;

private:
    EventHandler* eventHandler;
    QMap<int, std::function<CandleClose*()>> candleFactories;  // interval → factory
    QMap<int, QDateTime> lastDispatched;                       // interval → last close‐time we fired
};

#endif // CANDLECLOSEEVENTOBSERVER_H
